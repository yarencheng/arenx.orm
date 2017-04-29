
#pragma once

#include <vector>
#include "../interface/ResultRowInterface.hpp"
#include "SqliteResult.hpp"
#include "SqlitePreparedStatement.hpp"
#include "../foward_declare.hpp"

namespace arenx { namespace orm {

class SqliteRow: public ResultRowInterface{

	friend class SqliteResult;
	friend class SqliteDatastore;
	friend class SqlitePreparedStatement;

public:

	virtual ~SqliteRow () = default;

private:
	std::vector<std::shared_ptr<void> > _values;
	std::vector<std::size_t> _valueSizes;
	std::vector<int> _valueTypes;
	SqliteResult* _parent;
};

}}
