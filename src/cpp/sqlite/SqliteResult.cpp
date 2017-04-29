/*
 * SqliteResult.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "sqlite/SqliteResult.hpp"

using namespace ::std;
using namespace ::arenx::orm;

void SqliteResult::AddRow(std::shared_ptr<ResultRowInterface> row){
	_rows.push_back(row);
}

int SqliteResult::GetAsInt(){
	throw "TODO";
}

string SqliteResult::GetAsString(){
	throw "TODO";
}
