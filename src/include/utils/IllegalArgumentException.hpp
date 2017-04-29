/*
 * IllegalArgumentException.hpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#pragma once

#include "../OrmException.hpp"

#define ILLEGAL_ARGUMENT_EXCEPTION(...)	 IllegalArgumentException(__LINE__, __FILE__, ##__VA_ARGS__)

namespace arenx { namespace orm {

class IllegalArgumentException: public OrmException{

public:
	IllegalArgumentException(): OrmException() {};
	IllegalArgumentException(const int& line, const std::string& file): OrmException(line, file) {};
	IllegalArgumentException(const int& line, const std::string& file, const OrmException& cause): OrmException(line, file, cause) {};
	IllegalArgumentException(const int& line, const std::string& file, const std::exception& cause): OrmException(line, file, cause) {};
	IllegalArgumentException(const int& line, const std::string& file, const std::string &message): OrmException(line, file, message) {};
	IllegalArgumentException(const int& line, const std::string& file, const std::string &message, const OrmException& cause): OrmException(line, file, message, cause) {};
	IllegalArgumentException(const int& line, const std::string& file, const std::string &message, const std::exception& cause): OrmException(line, file, message, cause) {};

	virtual std::string GetName() const { return "IllegalArgumentException"; };

};

}}
