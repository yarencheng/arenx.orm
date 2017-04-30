/*
 * SqliteResult.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "sqlite/SqliteResult.hpp"

#include <iomanip>
#include "utils/Validator.hpp"

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

size_t SqliteResult::GetResultTitleIndex(const string& property)
{
	auto it = _resultIndexs.find(property);

	VALIDATE_TRUE(_resultIndexs.end() != it, "no such property [" + property + "]");

	return it->second;
}

ostream& SqliteResult::dump(ostream& os){
	if (_resultTitles.empty()) {
		return os;
	}

	vector<size_t> columnSize;
	for (string& s: _resultTitles) {
		columnSize.push_back(s.length());
	}

	for (shared_ptr<ResultRowInterface> row: _rows) {

		vector<string> values = row->getValues();
		for (size_t i = 0; i < values.size(); i++) {
			if (columnSize[i] < values[i].length()) {
				columnSize[i] = values[i].length();
			}
		}
	}

	for (size_t i = 0; i < _resultTitles.size(); i++) {
		if (0 != i) {
			os << "|";
		}
		os << setw(columnSize[i]) << left << _resultTitles[i];
	}
	os << endl;

	for (size_t i = 0; i < _resultTitles.size(); i++) {
		if (0 != i) {
			os << "+";
		}
		os << setw(columnSize[i]) << left << string(columnSize[i], '-');
	}
	os << endl;

	for (shared_ptr<ResultRowInterface> row: _rows) {

		vector<string> values = row->getValues();

		for (size_t i = 0; i < values.size(); i++) {
			if (0 != i) {
				os << "|";
			}
			os << setw(columnSize[i]) << left << values[i];
		}
		os << endl;
	}

	return os;
}
