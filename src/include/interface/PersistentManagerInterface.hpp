
#include <typeindex>
#include "PersistentAdaptorInterface.hpp"
#include "PreparedExecutionInterface.hpp"
#include "DatastoreInterface.hpp"

#pragma once

namespace arenx { namespace orm {

class PersistentManagerInterface{

public:

	virtual ~PersistentManagerInterface () = default;

	template<class PERSISTENCE>
	void makePersist(PERSISTENCE& p){

	}

	template<class PERSISTENCE, class KEY>
	PERSISTENCE getObjectById(const KEY& key){
//		return p;
	}

	virtual std::shared_ptr<DatastoreInterface> getDatastore() = 0;

protected:

	virtual std::shared_ptr<PreparedExecutionInterface> getSavePreparedExecution(const std::type_index& index) = 0;
	virtual std::shared_ptr<PreparedExecutionInterface> getLoadPreparedExecution(const std::type_index& index) = 0;

};

}}
