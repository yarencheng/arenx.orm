/*
 * Validator.hpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#pragma once

#include <memory>
#include "../common/IllegalArgumentException.hpp"

#define VALIDATE_NOT_NULL(ptr, message)		Validator::notNull(ptr, __LINE__, __FILE__, message)
#define VALIDATE_TRUE(condition, message) 	Validator::isTrue((condition), __LINE__, __FILE__, message)
#define VALIDATE_FALSE(condition, message) 	Validator::isFalse((condition), __LINE__, __FILE__, message)

namespace arenx { namespace orm {

class Validator{
public:
	virtual ~Validator() {};

	static void notNull(std::shared_ptr<void> ptr, int line, const std::string& file, const std::string& message);
	static void isTrue(bool condition, int line, const std::string& file, const std::string& message);
	static void isFalse(bool condition, int line, const std::string& file, const std::string& message);


private:
	Validator() {};
};

}}


