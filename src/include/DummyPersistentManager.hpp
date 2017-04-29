
#pragma once

#include <map>
#include "DummyDatastore.hpp"
#include "DummyPersistentAdaptor.hpp"
#include "interface/PersistentManagerInterface.hpp"


namespace arenx { namespace orm {

class DummyPersistentManager: public PersistentManagerInterface{

public:
	DummyPersistentManager();
	virtual ~DummyPersistentManager () = default;



protected:
	virtual std::shared_ptr<DatastoreInterface> getDatastore();
	virtual std::shared_ptr<PersistentAdaptorInterface> getPersistentAdaptor(const std::type_index& index);

private:
	std::shared_ptr<DummyDatastore> _datastore;
	std::shared_ptr<DummyPersistentAdaptor> _adaptor;

};

}}
