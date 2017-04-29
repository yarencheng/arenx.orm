/*
 * SqlitePreparedStatement.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "sqlite/SqlitePreparedStatement.hpp"

#include <cstring>
#include <boost/format.hpp>

using namespace ::std;
using namespace ::arenx::orm;

shared_ptr<ResultInterface> SqlitePreparedStatement::Execute(){

	shared_ptr<SqliteResult> result = make_shared<SqliteResult>();

	result->_resultTitles = _resultTitles;

	std::size_t index = 0;
	for (string& s: result->_resultTitles) {
		result->_resultIndexs[s] = index++;
	}

	while (SQLITE_ROW == sqlite3_step(_stmt.get())) {

		int columnCount = sqlite3_column_count(_stmt.get());

		shared_ptr<SqliteRow> row  = make_shared<SqliteRow>();

		for(int i=0; i<columnCount; i++){

			int type = sqlite3_column_type(_stmt.get(), i);
			row->_valueTypes.push_back(type);

			switch (type) {
			case SQLITE_NULL:{
				row->_valueSizes.push_back(0);

				row->_values.push_back(shared_ptr<void>(NULL));;

				break;
			}
			case SQLITE_FLOAT:{
				row->_valueSizes.push_back(sizeof(double));

				double d = sqlite3_column_double(_stmt.get(), i);
				row->_values.push_back(shared_ptr<double>(new double(d)));

				break;
			}
			case SQLITE_INTEGER:{
				row->_valueSizes.push_back(sizeof(int64_t));

				int64_t i64 = sqlite3_column_int64(_stmt.get(), i);
				row->_values.push_back(shared_ptr<int64_t>(new int64_t(i64)));

				break;
			}
			case SQLITE_BLOB:{
				std::size_t size = sqlite3_column_bytes(_stmt.get(), i);
				row->_valueSizes.push_back(size);

				const void* src = sqlite3_column_blob(_stmt.get(), i);
				shared_ptr<uint8_t> dst( new uint8_t[size], default_delete<uint8_t[]>() );

				if (!dst) {
					throw SQLITE_EXCEPTION("out of memory");
				}

				memcpy(dst.get(), src, size);

				row->_values.push_back(dst);

				break;
			}
			case SQLITE_TEXT:{
				const char* c = (const char*)sqlite3_column_text(_stmt.get(), i);
				std::size_t cSize = strlen(c);

				shared_ptr<char> buf( new char[cSize], default_delete<char[]>() );
				strncpy(buf.get(), c, cSize);

				row->_valueSizes.push_back(cSize);
				row->_values.push_back(buf);
				break;
			}
			default:
				throw SQLITE_EXCEPTION(boost::str(boost::format("unknown type [%1%]") % type));
			}
		}

		row->_parent = result.get();
		result->AddRow(row);
	}

	int status = sqlite3_reset(_stmt.get());
	if (SQLITE_OK != status) {
		throw SQLITE_EXCEPTION(boost::str(boost::format("Failed to execute prepared statement error=[%1%]") % status));
	}

	return result;
}
