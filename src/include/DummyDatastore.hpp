
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
		virtual std::ostream& dump(std::ostream& os) { return os; };
	};

	class DummyPreparedExecution: public PreparedExecutionInterface{
	public:
		virtual ~DummyPreparedExecution () = default;

		virtual std::shared_ptr<ResultInterface> Execute();
		virtual void Bind(int index, const int32_t value){};
		virtual void Bind(int index, const u_int32_t value){};
		virtual void Bind(int index, const int64_t value){};
		virtual void Bind(int index, const u_int64_t value){};
		virtual void Bind(int index, const double value){};
		virtual void Bind(int index, const std::string& value){};
	};

	DummyDatastore(){};
	virtual ~DummyDatastore () {};

	virtual std::shared_ptr<ResultInterface> Execute(const std::string& command);
	virtual std::shared_ptr<PreparedExecutionInterface> Prepare(const std::string& command);

};

}}
