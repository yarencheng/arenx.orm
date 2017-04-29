/*
 * SimplePersistentManager.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include <boost/format.hpp>
#include "SimplePersistentManager.hpp"

using namespace std;
using namespace arenx::orm;

SimplePersistentManager::SimplePersistentManager()
	: _datastore(make_shared<DummyDatastore>()){
//: _datastore(shared_ptr<DummyDatastore>(new DummyDatastore()))
//{

}

shared_ptr<DatastoreInterface> SimplePersistentManager::getDatastore(){
	return _datastore;
}

shared_ptr<PreparedExecutionInterface> SimplePersistentManager::getSavePreparedExecution(const type_index& index){

	auto it = _saveExecutions.find(index);

	if (_saveExecutions.end() != it) {
		return it->second;
	}

	throw runtime_error(boost::str(boost::format(
		"no such item %1%" )
		% index.name()
	));
}

shared_ptr<PreparedExecutionInterface> SimplePersistentManager::getLoadPreparedExecution(const type_index& index){

	auto it = _loadExecutions.find(index);

	if (_loadExecutions.end() != it) {
		return it->second;
	}

	throw runtime_error(boost::str(boost::format(
		"no such item %1%" )
		% index.name()
	));
}
