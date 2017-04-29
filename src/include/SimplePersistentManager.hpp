
#include <map>

#include "DummyDatastore.hpp"
#include "interface/PersistentManagerInterface.hpp"

#pragma once

namespace arenx { namespace orm {

class SimplePersistentManager: public PersistentManagerInterface{

public:
	SimplePersistentManager();
	virtual ~SimplePersistentManager () = default;

	virtual std::shared_ptr<DatastoreInterface> getDatastore();

protected:

	virtual std::shared_ptr<PreparedExecutionInterface> getSavePreparedExecution(const std::type_index& index);
	virtual std::shared_ptr<PreparedExecutionInterface> getLoadPreparedExecution(const std::type_index& index);

private:
	std::map<std::type_index, std::shared_ptr<PreparedExecutionInterface> > _saveExecutions;
	std::map<std::type_index, std::shared_ptr<PreparedExecutionInterface> > _loadExecutions;
	std::shared_ptr<DummyDatastore> _datastore;

};

}}
