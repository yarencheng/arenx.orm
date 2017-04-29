/*
 * SqliteResult.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "sqlite/SqliteResult.hpp"

using namespace ::std;
using namespace ::arenx::orm;

void SqliteResult::addRow(shared_ptr<ResultRowInterface> row){
	_rows.push_back(row);
}

void SqliteResult::forEach(const function<void(shared_ptr<ResultRowInterface>)>& fn)
{
	for (shared_ptr<ResultRowInterface> row: _rows) {
		fn(row);
	}
}
