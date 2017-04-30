
#pragma once

#include <vector>
#include <memory>
#include <sqlite3.h>
#include "../interface/PreparedExecutionInterface.hpp"
#include "SqliteResult.hpp"
#include "SqliteRow.hpp"
#include "SqliteException.hpp"
#include "../foward_declare.hpp"

namespace arenx { namespace orm {

class SqlitePreparedStatement: public PreparedExecutionInterface{

	friend class SqliteDatastore;

public:

	virtual ~SqlitePreparedStatement () = default;

	virtual std::shared_ptr<ResultInterface> Execute();
	virtual void Bind(int index, const int32_t value);
	virtual void Bind(int index, const u_int32_t value);
	virtual void Bind(int index, const int64_t value);
	virtual void Bind(int index, const u_int64_t value);
	virtual void Bind(int index, const double value);
	virtual void Bind(int index, const std::string& value);

private:
	std::shared_ptr<sqlite3_stmt> _stmt;
	std::vector<std::string> _resultTitles;

};

}}
