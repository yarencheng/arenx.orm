/*
 * SimplePersistentManager.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "DummyDatastore.hpp"

#include <boost/format.hpp>

using namespace std;
using namespace arenx::orm;

shared_ptr<ResultInterface> DummyDatastore::Execute(const string& command){
	return make_shared<DummyResult>();
}

shared_ptr<PreparedExecutionInterface> DummyDatastore::Prepare(const string& command){

	return make_shared<DummyPreparedExecution>();
}

shared_ptr<ResultInterface> DummyDatastore::DummyPreparedExecution::Execute(){
	return make_shared<DummyResult>();
}
