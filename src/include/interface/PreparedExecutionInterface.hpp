
#pragma once

#include <memory>
#include "ResultInterface.hpp"

namespace arenx { namespace orm {

class PreparedExecutionInterface{

public:

	virtual ~PreparedExecutionInterface () = default;

	virtual std::shared_ptr<ResultInterface> Execute() = 0;
};

}}
