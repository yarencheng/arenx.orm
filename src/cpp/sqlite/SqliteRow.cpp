/*
 * SqliteRow.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "sqlite/SqliteRow.hpp"

#include <sqlite3.h>
#include <boost/lexical_cast.hpp>
#include "common/IllegalArgumentException.hpp"

using namespace ::std;
using namespace ::arenx::orm;


int SqliteRow::getAsInt(const std::size_t& index)
{
	int type = _valueTypes.at(index);

	switch (type) {
	case SQLITE_NULL:{
		throw ILLEGAL_ARGUMENT_EXCEPTION("value is null");
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
			throw ILLEGAL_ARGUMENT_EXCEPTION("failed convert string [" + s + "] to int");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));
		try {
			return boost::lexical_cast<int>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw ILLEGAL_ARGUMENT_EXCEPTION("failed convert string [" + s + "] to int");
		}
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";
		throw ILLEGAL_ARGUMENT_EXCEPTION(ss.str());
	}
}


int SqliteRow::getAsInt(const std::string& property)
{
	size_t index = _parent->GetResultTitleIndex(property);

	return getAsInt(index);
}


uint32_t SqliteRow::getAsUint32(const std::string& property)
{
	size_t index = _parent->GetResultTitleIndex(property);

	return getAsUint32(index);
}

uint32_t SqliteRow::getAsUint32(const std::size_t& index)
{
	int type = _valueTypes.at(index);

	switch (type) {
	case SQLITE_NULL:{
		throw ILLEGAL_ARGUMENT_EXCEPTION("value is null");
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
			throw ILLEGAL_ARGUMENT_EXCEPTION("failed convert string [" + s + "] to uint32_t");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));
		try {
			return boost::lexical_cast<uint32_t>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw ILLEGAL_ARGUMENT_EXCEPTION("failed convert string [" + s + "] to uint32_t");
		}
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";
		throw ILLEGAL_ARGUMENT_EXCEPTION(ss.str());
	}
}

int64_t SqliteRow::getAsInt64(const std::size_t& index)
{
	int type = _valueTypes.at(index);

	switch (type) {
	case SQLITE_NULL:{
		throw ILLEGAL_ARGUMENT_EXCEPTION("value is null");
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
			throw ILLEGAL_ARGUMENT_EXCEPTION("failed convert string [" + s + "] to int64_t");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));
		try {
			return boost::lexical_cast<int64_t>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw ILLEGAL_ARGUMENT_EXCEPTION("failed convert string [" + s + "] to int64_t");
		}
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";

		throw ILLEGAL_ARGUMENT_EXCEPTION(ss.str());
	}
}

int64_t SqliteRow::getAsInt64(const std::string& property)
{
	size_t index = _parent->GetResultTitleIndex(property);

	return getAsInt64(index);
}

uint64_t SqliteRow::getAsUint64(const std::size_t& index)
{
	int type = _valueTypes.at(index);

	switch (type) {
	case SQLITE_NULL:{
		throw ILLEGAL_ARGUMENT_EXCEPTION("value is null");
	}
	case SQLITE_FLOAT:{
		return (uint64_t)*(double*)_values.at(index).get();
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
			throw ILLEGAL_ARGUMENT_EXCEPTION("failed convert string [" + s + "] to uint64_t");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));
		try {
			return boost::lexical_cast<uint64_t>(s);
		} catch (boost::bad_lexical_cast& e) {
			throw ILLEGAL_ARGUMENT_EXCEPTION("failed convert string [" + s + "] to uint64_t");
		}
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";
		throw ILLEGAL_ARGUMENT_EXCEPTION(ss.str());
	}
}

double SqliteRow::getAsDouble(const std::string& property)
{
	size_t index = _parent->GetResultTitleIndex(property);

	return getAsDouble(index);
}

double SqliteRow::getAsDouble(const std::size_t& index)
{
	int type = _valueTypes.at(index);

	switch (type) {
	case SQLITE_NULL:{
		throw ILLEGAL_ARGUMENT_EXCEPTION("value is null");
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
			throw ILLEGAL_ARGUMENT_EXCEPTION("failed convert string [" + s + "] to double");
		}
	}
	case SQLITE_TEXT:{
		string s((char*)_values.at(index).get(), _valueSizes.at(index));

		stringstream ss;
		ss << s;

		double d;
		ss >> d;

		return d;
	}
	default:
		stringstream ss;
		ss << "unknown sqlite type [" << type << "]";
		throw ILLEGAL_ARGUMENT_EXCEPTION(ss.str());
	}
}

uint64_t SqliteRow::getAsUint64(const std::string& property)
{
	size_t index = _parent->GetResultTitleIndex(property);

	return getAsUint64(index);
}

string SqliteRow::getAsString(const std::size_t& index)
{
	int type = _valueTypes.at(index);

	switch (type) {
	case SQLITE_NULL:{
		throw ILLEGAL_ARGUMENT_EXCEPTION("value is null");
	}
	case SQLITE_FLOAT:{
		double d = *(double*)_values.at(index).get();
		try {
			return boost::lexical_cast<string>(d);
		} catch (boost::bad_lexical_cast& e) {
			stringstream ss;
			ss << "failed convert double [" << d << "] to string";
			throw ILLEGAL_ARGUMENT_EXCEPTION(ss.str());
		}
	}
	case SQLITE_INTEGER:{
		int64_t i = *(int64_t*)_values.at(index).get();
		try {
			return boost::lexical_cast<string>(i);
		} catch (boost::bad_lexical_cast& e) {
			stringstream ss;
			ss << "failed convert int64_t [" << i << "] to string";
			throw ILLEGAL_ARGUMENT_EXCEPTION(ss.str());
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
		throw ILLEGAL_ARGUMENT_EXCEPTION(ss.str());
	}
}

string SqliteRow::getAsString(const std::string& property)
{
	size_t index = _parent->GetResultTitleIndex(property);

	return getAsString(index);
}
