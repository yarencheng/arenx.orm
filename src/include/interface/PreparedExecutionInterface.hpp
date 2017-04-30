
#pragma once

#include <string>
#include <memory>
#include "ResultInterface.hpp"

namespace arenx { namespace orm {

class PreparedExecutionInterface{

public:

	virtual ~PreparedExecutionInterface () = default;

	virtual std::shared_ptr<ResultInterface> Execute() = 0;

	virtual void Bind(int index, const int32_t value) = 0;
	virtual void Bind(int index, const u_int32_t value) = 0;
	virtual void Bind(int index, const int64_t value) = 0;
	virtual void Bind(int index, const u_int64_t value) = 0;
	virtual void Bind(int index, const double value) = 0;
	virtual void Bind(int index, const std::string& value) = 0;
};

}}
