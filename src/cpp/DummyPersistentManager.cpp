/*
 * SimplePersistentManager.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "DummyPersistentManager.hpp"

#include <boost/format.hpp>

using namespace std;
using namespace arenx::orm;

DummyPersistentManager::DummyPersistentManager()
	: _datastore(make_shared<DummyDatastore>())
	, _adaptor(make_shared<DummyPersistentAdaptor>())
{

}

shared_ptr<DatastoreInterface> DummyPersistentManager::getDatastore(){
	return _datastore;
}

shared_ptr<PersistentAdaptorInterface> DummyPersistentManager::getPersistentAdaptor(const type_index& index){
	return _adaptor;
}

