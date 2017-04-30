/*
 * SqliteRow.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "sqlite/SqliteRow.hpp"

#include <sqlite3.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "common/IllegalArgumentException.hpp"

using namespace ::std;
using namespace ::arenx::orm;


int32_t SqliteRow::getAsInt32(const std::size_t& index)
{
	int type;

	try {
		type = _valueTypes.at(index);
	} catch (out_of_range& e) {
		throw ILLEGAL_ARGUMENT_EXCEPTION("out of range [" + to_string(index) + "]", e);
	}

	switch (type) {
	case SQLITE_NULL:{
		throw SQLITE_EXCEPTION("value is null");
	}
	case SQLITE_FLOAT:{
		return (int)*(double*)_values.at(index).get();
	}
	case SQLITE_INTEGER:{
		return (int)*(int64_t*)_values.at(index).get();
	}
	case SQLITE_BLOB:{
		const char* c = (const char*)_values.at(index).get();
		string s(c, _valueSizes.at(index));
		try {
			return boost::lexical_cast<int>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to int");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));
		try {
			return boost::lexical_cast<int>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to int");
		}
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";
		throw SQLITE_EXCEPTION(ss.str());
	}
}


int32_t SqliteRow::getAsInt32(const std::string& property)
{
	auto spt = _parent.lock();

	if (!spt) {
		throw SQLITE_EXCEPTION("SQLite result is deleted in memory. Use getAsInt(std::size_t) instead.");
	}

	std::size_t index = spt->GetResultTitleIndex(property);

	return getAsInt32(index);
}


uint32_t SqliteRow::getAsUint32(const std::string& property)
{
	auto spt = _parent.lock();

	if (!spt) {
		throw SQLITE_EXCEPTION("SQLite result is deleted in memory. Use getAsInt(std::size_t) instead.");
	}

	std::size_t index = spt->GetResultTitleIndex(property);

	return getAsUint32(index);
}

uint32_t SqliteRow::getAsUint32(const std::size_t& index)
{
	int type;

	try {
		type = _valueTypes.at(index);
	} catch (out_of_range& e) {
		throw ILLEGAL_ARGUMENT_EXCEPTION("out of range [" + to_string(index) + "]", e);
	}

	switch (type) {
	case SQLITE_NULL:{
		throw SQLITE_EXCEPTION("value is null");
	}
	case SQLITE_FLOAT:{
		return (uint32_t)*(double*)_values.at(index).get();
	}
	case SQLITE_INTEGER:{
		return (uint32_t)*(int64_t*)_values.at(index).get();
	}
	case SQLITE_BLOB:{
		const char* c = (const char*)_values.at(index).get();
		string s(c, _valueSizes.at(index));
		try {
			return boost::lexical_cast<uint32_t>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to uint32_t");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));
		try {
			return boost::lexical_cast<uint32_t>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to uint32_t");
		}
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";
		throw SQLITE_EXCEPTION(ss.str());
	}
}

int64_t SqliteRow::getAsInt64(const std::size_t& index)
{
	int type;

	try {
		type = _valueTypes.at(index);
	} catch (out_of_range& e) {
		throw ILLEGAL_ARGUMENT_EXCEPTION("out of range [" + to_string(index) + "]", e);
	}

	switch (type) {
	case SQLITE_NULL:{
		throw SQLITE_EXCEPTION("value is null");
	}
	case SQLITE_FLOAT:{
		return (int64_t)*(double*)_values.at(index).get();
	}
	case SQLITE_INTEGER:{
		return *(int64_t*)_values.at(index).get();
	}
	case SQLITE_BLOB:{
		const char* c = (const char*)_values.at(index).get();
		string s(c, _valueSizes.at(index));
		try {
			return boost::lexical_cast<int64_t>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to int64_t");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));
		try {
			return boost::lexical_cast<int64_t>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to int64_t");
		}
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";

		throw SQLITE_EXCEPTION(ss.str());
	}
}

int64_t SqliteRow::getAsInt64(const std::string& property)
{
	auto spt = _parent.lock();

	if (!spt) {
		throw SQLITE_EXCEPTION("SQLite result is deleted in memory. Use getAsInt(std::size_t) instead.");
	}

	std::size_t index = spt->GetResultTitleIndex(property);

	return getAsInt64(index);
}

uint64_t SqliteRow::getAsUint64(const std::size_t& index)
{
	int type;

	try {
		type = _valueTypes.at(index);
	} catch (out_of_range& e) {
		throw ILLEGAL_ARGUMENT_EXCEPTION("out of range [" + to_string(index) + "]", e);
	}

	switch (type) {
	case SQLITE_NULL:{
		throw SQLITE_EXCEPTION("value is null");
	}
	case SQLITE_FLOAT:{
		return *(double*)_values.at(index).get();
	}
	case SQLITE_INTEGER:{
		return (uint64_t)*(int64_t*)_values.at(index).get();
	}
	case SQLITE_BLOB:{
		const char* c = (const char*)_values.at(index).get();
		string s(c, _valueSizes.at(index));
		try {
			return boost::lexical_cast<uint64_t>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to uint64_t");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));
		try {
			return boost::lexical_cast<uint64_t>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to uint64_t");
		}
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";
		throw SQLITE_EXCEPTION(ss.str());
	}
}

double SqliteRow::getAsDouble(const std::string& property)
{
	auto spt = _parent.lock();

	if (!spt) {
		throw SQLITE_EXCEPTION("SQLite result is deleted in memory. Use getAsInt(std::size_t) instead.");
	}

	std::size_t index = spt->GetResultTitleIndex(property);

	return getAsDouble(index);
}

double SqliteRow::getAsDouble(const std::size_t& index)
{
	int type;

	try {
		type = _valueTypes.at(index);
	} catch (out_of_range& e) {
		throw ILLEGAL_ARGUMENT_EXCEPTION("out of range [" + to_string(index) + "]", e);
	}

	switch (type) {
	case SQLITE_NULL:{
		throw SQLITE_EXCEPTION("value is null");
	}
	case SQLITE_FLOAT:{
		return *(double*)_values.at(index).get();
	}
	case SQLITE_INTEGER:{
		return (double)*(int64_t*)_values.at(index).get();
	}
	case SQLITE_BLOB:{
		const char* c = (const char*)_values.at(index).get();
		string s(c, _valueSizes.at(index));

		try {
			return boost::lexical_cast<double>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to double");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));
		try {
			return boost::lexical_cast<double>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw SQLITE_EXCEPTION("failed convert string [" + s + "] to double");
		}
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";
		throw SQLITE_EXCEPTION(ss.str());
	}
}

uint64_t SqliteRow::getAsUint64(const std::string& property)
{
	auto spt = _parent.lock();

	if (!spt) {
		throw SQLITE_EXCEPTION("SQLite result is deleted in memory. Use getAsInt(std::size_t) instead.");
	}

	std::size_t index = spt->GetResultTitleIndex(property);

	return getAsUint64(index);
}

string SqliteRow::getAsString(const std::size_t& index)
{
	int type;

	try {
		type = _valueTypes.at(index);
	} catch (out_of_range& e) {
		throw ILLEGAL_ARGUMENT_EXCEPTION("out of range [" + to_string(index) + "]", e);
	}

	switch (type) {
	case SQLITE_NULL:{
		throw SQLITE_EXCEPTION("value is null");
	}
	case SQLITE_FLOAT:{
		double d = *(double*)_values.at(index).get();
		try {
			return boost::lexical_cast<string>(d);
		} catch (boost::bad_lexical_cast& e) {
			stringstream ss;
			ss << "failed convert double [" << d << "] to string";
			throw SQLITE_EXCEPTION(ss.str());
		}
	}
	case SQLITE_INTEGER:{
		int64_t i = *(int64_t*)_values.at(index).get();
		try {
			return boost::lexical_cast<string>(i);
		} catch (boost::bad_lexical_cast& e) {
			stringstream ss;
			ss << "failed convert int64_t [" << i << "] to string";
			throw SQLITE_EXCEPTION(ss.str());
		}
	}
	case SQLITE_BLOB:{
		const char* c = (const char*)_values.at(index).get();
		return string(c, _valueSizes.at(index));
	}
	case SQLITE_TEXT:{
		return 	string ((char*)_values.at(index).get(), _valueSizes.at(index));
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";
		throw SQLITE_EXCEPTION(ss.str());
	}
}

string SqliteRow::getAsString(const std::string& property)
{
	auto spt = _parent.lock();

	if (!spt) {
		throw SQLITE_EXCEPTION("SQLite result is deleted in memory. Use getAsInt(std::size_t) instead.");
	}

	std::size_t index = spt->GetResultTitleIndex(property);

	return getAsString(index);
}

vector<std::string> SqliteRow::GetValues()
{
	vector<string> out;

	for (size_t i = 0; i < _values.size(); i++) {

		int valueType = _valueTypes.at(i);

		switch (valueType) {
		case SQLITE_NULL:
			out.push_back("(NULL)");
			break;
		case SQLITE_BLOB:{
			size_t size = _valueSizes.at(i);
			const char* c = (const char*)_values.at(i).get();

			stringstream ss;
			ss << "0x";

			for (size_t i = 0; i < size ; i++) {
				ss << hex << ((int)(uint8_t)c[i]);
			}

			out.push_back(ss.str());

			break;
		}
		case SQLITE_TEXT:
			out.push_back(getAsString(i));
			break;
		case SQLITE_FLOAT:
			out.push_back(boost::lexical_cast<string>(getAsDouble(i)));
			break;
		case SQLITE_INTEGER:
			out.push_back(boost::lexical_cast<string>(getAsInt64(i)));
			break;
		default:
			stringstream ss;
			ss << "unknown sqlite type [" << valueType << "]";
			throw SQLITE_EXCEPTION(ss.str());
		}
	}

	return out;
}
