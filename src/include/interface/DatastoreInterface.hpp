#include <memory>
#include "PreparedExecutionInterface.hpp"
#include "ResultInterface.hpp"

#pragma once

namespace arenx { namespace orm {

class DatastoreInterface{

public:

	virtual ~DatastoreInterface () = default;

	virtual std::shared_ptr<ResultInterface> Execute(const std::string& command) = 0;
	virtual std::shared_ptr<PreparedExecutionInterface> Prepare(const std::string& command) = 0;

};

}}
