
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
		auto adaptor = getPersistentAdaptor(std::type_index(typeid(PERSISTENCE)));
		adaptor->write();

		p.adapt(*adaptor);

		adaptor->execute();
	}

	template<class PERSISTENCE, class KEY>
	PERSISTENCE getObjectById(const KEY& key){
		auto adaptor = getPersistentAdaptor(std::type_index(typeid(PERSISTENCE)));
		adaptor->read(key);

		PERSISTENCE p;
		p.adapt(*adaptor);

		adaptor->execute();

		return p;
	}



protected:

	virtual std::shared_ptr<DatastoreInterface> getDatastore() = 0;
	virtual std::shared_ptr<PersistentAdaptorInterface> getPersistentAdaptor(const std::type_index& index) = 0;

};

}}
