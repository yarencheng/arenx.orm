
#pragma once

#include <memory>
#include <sqlite3.h>
#include "interface/DatastoreInterface.hpp"
#include "SqliteException.hpp"

namespace arenx { namespace orm {

class SqliteDatastore: public DatastoreInterface{

public:

	SqliteDatastore(const std::string& uri);
	virtual ~SqliteDatastore () ;

	virtual std::shared_ptr<ResultInterface> Execute(const std::string& command);
	virtual std::shared_ptr<PreparedExecutionInterface> Prepare(const std::string& command);

private:
	static int execCallback(void* context, int rowSize, char **rowValues, char **columnName);

	std::shared_ptr<sqlite3> _conn;

	void connect(const std::string& uri);

};

}}
