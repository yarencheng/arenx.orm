/*
 * OrmException.hpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#pragma once

#include <string>
#include <exception>

#define ORM_EXCEPTION(...)	 OrmException(__LINE__, __FILE__, ##__VA_ARGS__)

namespace arenx { namespace orm{

class OrmException: public std::exception{

public:
	OrmException();
	OrmException(const int& line, const std::string& file);
	OrmException(const int& line, const std::string& file, const OrmException& cause);
	OrmException(const int& line, const std::string& file, const std::exception& cause);
	OrmException(const int& line, const std::string& file, const std::string &message);
	OrmException(const int& line, const std::string& file, const std::string &message, const OrmException& cause);
	OrmException(const int& line, const std::string& file, const std::string &message, const std::exception& cause);

	virtual std::string GetName() const { return "OrmException"; };
	virtual std::string GetMessage() const { return _message; };
	virtual std::string GetStackTrace() const { return _stackTrace; };
	virtual const char* what() const throw() { return _message.c_str(); };

protected:
	std::string CreateMessage(const int* line, const std::string* file, const std::string* message, const OrmException* baseCause, const std::exception* stdCause);
	std::string CreateCurrentStacktrace(const int* line, const std::string* file, const std::string* message, const OrmException* baseCause, const std::exception* stdCause);

private:
	std::string _message;
	std::string _stackTrace;

};

}}




