

#pragma once

#include <memory>
#include "ResultRowInterface.hpp"

namespace arenx { namespace orm {

class ResultInterface{

public:

	virtual ~ResultInterface () = default;

	virtual void AddRow(std::shared_ptr<ResultRowInterface> row) = 0;
	virtual int GetAsInt() = 0;
	virtual std::string GetAsString() = 0;

};

}}
