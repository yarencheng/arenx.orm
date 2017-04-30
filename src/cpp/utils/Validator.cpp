/*
 * Validator.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "utils/Validator.hpp"

using namespace ::std;
using namespace ::arenx::orm;

void Validator::notNull(shared_ptr<void> ptr, int line, const std::string& file, const std::string& message){
	if (ptr) {
		return;
	}

	throw IllegalArgumentException(line, file, message);
}

void Validator::isTrue(bool condition, int line, const std::string& file, const std::string& message){
	if (condition) {
		return;
	}

	throw IllegalArgumentException(line, file, message);
}

void Validator::isFalse(bool condition, int line, const std::string& file, const std::string& message){
	if (!condition) {
		return;
	}

	throw IllegalArgumentException(line, file, message);
}
