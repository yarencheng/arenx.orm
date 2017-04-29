
#pragma once

#include <vector>
#include <map>
#include <list>
#include <functional>
#include "../interface/ResultInterface.hpp"
#include "SqliteRow.hpp"
#include "SqlitePreparedStatement.hpp"
#include "../foward_declare.hpp"

namespace arenx { namespace orm {

class SqliteResult: public ResultInterface{

	friend class SqliteDatastore;
	friend class SqlitePreparedStatement;

public:

	virtual ~SqliteResult () = default;

	virtual void forEach(const std::function<void(std::shared_ptr<ResultRowInterface>)>& fn);

private:
	std::vector<std::string> _resultTitles;
	std::map<std::string, std::size_t> _resultIndexs;
	std::list<std::shared_ptr<ResultRowInterface> > _rows;

	virtual void addRow(std::shared_ptr<ResultRowInterface> row);
};

}}
