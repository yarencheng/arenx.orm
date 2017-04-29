
#include "sqlite/SqliteDatastore.hpp"

#include <cstring>
#include <boost/format.hpp>
#include <utils/Validator.hpp>
#include "sqlite/SqliteResult.hpp"
#include "sqlite/SqlitePreparedStatement.hpp"

using namespace ::std;
using namespace ::arenx::orm;

SqliteDatastore::SqliteDatastore(const string& uri){
	connect(uri);
}

SqliteDatastore::~SqliteDatastore (){

}

int SqliteDatastore::execCallback(void* context, int rowSize, char **rowValues, char **columnName)
{
	shared_ptr<SqliteResult> result = *(shared_ptr<SqliteResult>*)context;

	if (result->_resultTitles.empty()) {
		for(int i=0; i<rowSize; i++){
			result->_resultTitles.push_back(columnName[i]);
		}

		std::size_t index = 0;
		for (string& s: result->_resultTitles) {
			result->_resultIndexs[s] = index++;
		}
	}

	shared_ptr<SqliteRow> row = make_shared<SqliteRow>();

	for(int i=0; i<rowSize; i++){
		if (NULL == rowValues[i]) {
			row->_valueTypes.push_back(SQLITE_NULL);
			row->_valueSizes.push_back(0);
			row->_values.push_back(shared_ptr<uint8_t>(NULL));
		} else {
			row->_valueTypes.push_back(SQLITE_TEXT);

			const char* c = rowValues[i];
			std::size_t cSize = strlen(c);

			shared_ptr<char> buf( new char[cSize], default_delete<char[]>() );
			strncpy(buf.get(), c, cSize);

			row->_valueSizes.push_back(cSize);
			row->_values.push_back(buf);
		}
	}

	row->_parent = result.get();
	result->AddRow(row);

	return 0;
}

shared_ptr<ResultInterface> SqliteDatastore::Execute(const string& command){
	if (!_conn) {
		throw SQLITE_EXCEPTION("database is not connected");
	}

	char* error = nullptr;
	shared_ptr<SqliteResult> result = make_shared<SqliteResult>();

	int status= sqlite3_exec(_conn.get(), command.c_str(), &SqliteDatastore::execCallback, &result, &error);

	if (SQLITE_OK != status) {
		string s = boost::str(boost::format("Failed to execute SQL=[%1%] error=[%2%]") % command % error);
		sqlite3_free(error);
		throw SQLITE_EXCEPTION(s);
	}

	return result;
}

shared_ptr<PreparedExecutionInterface> SqliteDatastore::Prepare(const string& command){

	if (!_conn) {
		throw SQLITE_EXCEPTION("database is not connected");
	}

	sqlite3_stmt* stmt = NULL;

	int status = sqlite3_prepare_v2(_conn.get(), command.c_str(), command.length(), &stmt, NULL);
	if (SQLITE_OK != status) {
		string s = boost::str(boost::format("Failed to prepare SQL=[%1%] status=[%2%]") % command % status);
		throw SQLITE_EXCEPTION(s);
	}

	shared_ptr<SqlitePreparedStatement> prepared = make_shared<SqlitePreparedStatement>();

	prepared->_stmt = shared_ptr<sqlite3_stmt> (stmt, [](sqlite3_stmt* p){
		sqlite3_finalize(p);
	});

	int columnCount = sqlite3_column_count(prepared->_stmt.get());

	for(int i=0; i<columnCount; i++){
		string name = sqlite3_column_name(prepared->_stmt.get(), i);
		prepared->_resultTitles.push_back(name);
	}

	return prepared;
}

void SqliteDatastore::connect(const std::string& uri){

	sqlite3* db = NULL;

	if(sqlite3_open_v2(
			uri.c_str(),
			&db,
			SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI | SQLITE_OPEN_CREATE,
			NULL)){
		throw SQLITE_EXCEPTION("Can't open sqlite database with uri [" + uri + "]");
	}

	_conn = shared_ptr<sqlite3>(db, [](sqlite3 *p){ if (p) sqlite3_close(p);});

	Execute("PRAGMA foreign_keys = ON;"); // TODO: fine tune
}

