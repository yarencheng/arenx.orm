/*
 * SqliteException.hpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#pragma once

#include "../OrmException.hpp"

#define SQLITE_EXCEPTION(...)	 SqliteException(__LINE__, __FILE__, ##__VA_ARGS__)

namespace arenx { namespace orm{

class SqliteException: public OrmException{

public:
	SqliteException(): OrmException() {};
	SqliteException(const int& line, const std::string& file): OrmException(line, file) {};
	SqliteException(const int& line, const std::string& file, const OrmException& cause): OrmException(line, file, cause) {};
	SqliteException(const int& line, const std::string& file, const std::exception& cause): OrmException(line, file, cause) {};
	SqliteException(const int& line, const std::string& file, const std::string &message): OrmException(line, file, message) {};
	SqliteException(const int& line, const std::string& file, const std::string &message, const OrmException& cause): OrmException(line, file, message, cause) {};
	SqliteException(const int& line, const std::string& file, const std::string &message, const std::exception& cause): OrmException(line, file, message, cause) {};

	virtual std::string GetName() const { return "SqliteException"; };

};

}}
