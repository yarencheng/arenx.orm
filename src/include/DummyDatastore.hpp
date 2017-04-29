
#pragma once

#include <memory>
#include "interface/DatastoreInterface.hpp"

namespace arenx { namespace orm {

class DummyDatastore: public DatastoreInterface{

public:

	class DummyResult: public ResultInterface{
	public:
		virtual ~DummyResult () = default;
		virtual void forEach(const std::function<void(std::shared_ptr<ResultRowInterface>)>&) {};
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
