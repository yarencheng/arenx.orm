
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

shared_ptr<ResultInterface> SqliteDatastore::Execute(const string& command){
	return Prepare(command)->Execute();
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

