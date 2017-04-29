#include <memory>
#include "interface/DatastoreInterface.hpp"

#pragma once

namespace arenx { namespace orm {

class DummyDatastore: public DatastoreInterface{

public:

	class DummyResult: public ResultInterface{
	public:
		virtual ~DummyResult () = default;
	};

	class DummyPreparedExecution: public PreparedExecutionInterface{
	public:
		virtual ~DummyPreparedExecution () = default;

		virtual std::shared_ptr<ResultInterface> Execute();
	};

	DummyDatastore(){};
	virtual ~DummyDatastore () {};

	virtual std::shared_ptr<ResultInterface> Execute(const std::string& command);
	virtual std::shared_ptr<PreparedExecutionInterface> Prepare(const std::string& command);

};

}}
