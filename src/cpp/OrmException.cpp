/*
 * OrmException.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>
#include "OrmException.hpp"

using namespace std;
using namespace arenx::orm;

OrmException::OrmException()
{
	_message = CreateMessage(NULL, NULL, NULL, NULL, NULL);
	_stackTrace = CreateCurrentStacktrace(NULL, NULL, NULL, NULL, NULL);
}

OrmException::OrmException(const int& line, const string& file)
{
	_message = CreateMessage(&line, &file, NULL, NULL, NULL);
	_stackTrace = CreateCurrentStacktrace(&line, &file, NULL, NULL, NULL);
}

OrmException::OrmException(const int& line, const string& file, const OrmException& cause)
{
	_message = CreateMessage(&line, &file, NULL, &cause, NULL);
	_stackTrace = CreateCurrentStacktrace(&line, &file, NULL, &cause, NULL);
}

OrmException::OrmException(const int& line, const string& file, const exception& cause)
{
	_message = CreateMessage(&line, &file, NULL, NULL, &cause);
	_stackTrace = CreateCurrentStacktrace(&line, &file, NULL, NULL, &cause);
}

OrmException::OrmException(const int& line, const string& file, const string &message)
{
	_message = CreateMessage(&line, &file, &message, NULL, NULL);
	_stackTrace = CreateCurrentStacktrace(&line, &file, &message, NULL, NULL);
}

OrmException::OrmException(const int& line, const string& file, const string &message, const OrmException& cause)
{
	_message = CreateMessage(&line, &file, &message, &cause, NULL);
	_stackTrace = CreateCurrentStacktrace(&line, &file, &message, &cause, NULL);
}

OrmException::OrmException(const int& line, const string& file, const string &message, const exception& cause)
{
	_message = CreateMessage(&line, &file, &message, NULL, &cause);
	_stackTrace = CreateCurrentStacktrace(&line, &file, &message, NULL, &cause);
}

string OrmException::CreateMessage(const int* line, const string* file, const string* message, const OrmException* baseCause, const exception* stdCause)
{
	stringstream ss;

	if (file) {
		ss << *file;
	} else {
		ss << "unknown";
	}

	if (line) {
		ss << "(" << *line << "): ";
	} else {
		ss << ": ";
	}

	ss << GetName() << ": ";

	if (message) {
		ss << *message << " ";
	}

	if (baseCause) {
		ss << " Caused by: " << baseCause->GetMessage();
	}

	if (stdCause) {
		ss << " Caused by: std::exception: " << stdCause->what();
	}

	return ss.str();
}

/**
 * Ref https://panthema.net/2008/0901-stacktrace-demangled/
 */
string OrmException::CreateCurrentStacktrace(const int* line, const std::string* file, const std::string* message, const OrmException* baseCause, const std::exception* stdCause)
{
	unsigned int max_frames = 63;
	stringstream ss;


	if (file) {
		ss << *file;
	} else {
		ss << "unknown";
	}

	if (line) {
		ss << "(" << *line << "): ";
	} else {
		ss << ": ";
	}

	ss << GetName() << ": ";

	if (message) {
		ss << *message << " ";
	}

	if (stdCause) {
		ss << " Caused by: std::exception: " << stdCause->what();
	}

	ss << endl;

	ss << "    stack trace:" << endl;

	// storage array for stack trace address data
	void* addrlist[max_frames+1];

	// retrieve current stack addresses
	int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

	if (addrlen == 0) {
		ss << "      <empty, possibly corrupt>" << endl;
		return ss.str();
	}

	// resolve addresses into strings containing "filename(function+address)",
	// this array must be free()-ed
	char** symbollist = backtrace_symbols(addrlist, addrlen);

	// allocate string which will be filled with the demangled function name
	size_t funcnamesize = 256;
	char* funcname = (char*)malloc(funcnamesize);

	// iterate over the returned symbol lines. skip the first, it is the
	// address of this function.
	for (int i = 1; i < addrlen; i++)
	{
		char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

		// find parentheses and +address offset surrounding the mangled name:
		// ./module(function+0x15c) [0x8048a6d]
		for (char *p = symbollist[i]; *p; ++p)
		{
			if (*p == '(')
				begin_name = p;
			else if (*p == '+')
				begin_offset = p;
			else if (*p == ')' && begin_offset) {
				end_offset = p;
				break;
			}
		}

		if (begin_name && begin_offset && end_offset
			&& begin_name < begin_offset)
		{
			*begin_name++ = '\0';
			*begin_offset++ = '\0';
			*end_offset = '\0';

			// mangled name is now in [begin_name, begin_offset) and caller
			// offset in [begin_offset, end_offset). now apply
			// __cxa_demangle():

			int status;
			char* ret = abi::__cxa_demangle(begin_name,
							funcname, &funcnamesize, &status);
			if (status == 0) {
				funcname = ret; // use possibly realloc()-ed string
				ss << "      " << symbollist[i] << " : " << funcname << "+" << begin_offset << endl;
			}
			else {
			// demangling failed. Output function name as a C function with
			// no arguments.
				ss << "      " << symbollist[i] << " : " << begin_name << "()+" << begin_offset << endl;
			}
		}
		else
		{
			// couldn't parse the line? print the whole line.
			ss << "      " << symbollist[i] << endl;
		}
	}

	free(funcname);
	free(symbollist);

	if (baseCause) {
		ss << baseCause->GetStackTrace() << endl;
	}

	return ss.str();
}

