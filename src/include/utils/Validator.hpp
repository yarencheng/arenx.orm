/*
 * Validator.hpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#pragma once

#include <memory>
#include "IllegalArgumentException.hpp"

#define VALIDATE_NOT_NULL(ptr, message) Validator::notNull(ptr, __LINE__, __FILE__, message)

namespace arenx { namespace orm {

class Validator{
public:
	virtual ~Validator() {};

	static void notNull(std::shared_ptr<void> ptr, int line, const std::string& file, const std::string& message);

private:
	Validator() {};
};

}}


