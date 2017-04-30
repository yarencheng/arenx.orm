
#pragma once

#include <vector>
#include "../interface/ResultRowInterface.hpp"
#include "SqliteResult.hpp"
#include "SqlitePreparedStatement.hpp"
#include "SqliteException.hpp"
#include "../foward_declare.hpp"

namespace arenx { namespace orm {

class SqliteRow: public ResultRowInterface{

	friend class SqliteResult;
	friend class SqliteDatastore;
	friend class SqlitePreparedStatement;

public:

	virtual ~SqliteRow () = default;

	virtual int32_t getAsInt32(const std::size_t& index);
	virtual int32_t getAsInt32(const std::string& property);
	virtual uint32_t getAsUint32(const std::size_t& index);
	virtual uint32_t getAsUint32(const std::string& property);
	virtual int64_t getAsInt64(const std::size_t& index);
	virtual int64_t getAsInt64(const std::string& property);
	virtual uint64_t getAsUint64(const std::size_t& index);
	virtual uint64_t getAsUint64(const std::string& property);
	virtual double getAsDouble(const std::size_t& index);
	virtual double getAsDouble(const std::string& property);
	virtual std::string getAsString(const std::size_t& index);
	virtual std::string getAsString(const std::string& property);

	virtual bool isNull(const std::size_t& index);
	virtual bool isNull(const std::string& property);

	virtual std::vector<std::string> getValues();

private:
	std::vector<std::shared_ptr<void> > _values;
	std::vector<std::size_t> _valueSizes;
	std::vector<int> _valueTypes;
	std::weak_ptr<SqliteResult> _parent;
};

}}
