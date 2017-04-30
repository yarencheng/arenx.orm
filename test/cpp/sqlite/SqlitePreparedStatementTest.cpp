/*
 * SqliteDatastoreTest.cpp
 *
 *  Created on: 2017年4月23日
 *      Author: arenx
 */

#include "sqlite/SqlitePreparedStatement.hpp"
#include "sqlite/SqliteDatastore.hpp"
#include "sqlite/SqliteRow.hpp"
#include "common/IllegalArgumentException.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::std;
using namespace ::testing;
using namespace ::arenx::orm;


using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;

namespace arenx { namespace orm { namespace SqlitePreparedStatementTest {

class SqlitePreparedStatementTest  : public Test {
protected:

	shared_ptr<SqliteDatastore> sqlite;

	virtual void SetUp() {
		sqlite = make_shared<SqliteDatastore>(":memory:");
	}

	virtual void TearDown() {
		sqlite = nullptr;
	}
};

TEST_F(SqlitePreparedStatementTest, Bind_int32){
	sqlite->Execute("CREATE TABLE test (value INTEGER);");

	shared_ptr<PreparedExecutionInterface> prepared = sqlite->Prepare("INSERT INTO test VALUES (?1)");

	int32_t expectValue = 123;

	prepared->Bind(1, expectValue);
	prepared->Execute();

	shared_ptr<ResultInterface> result = sqlite->Prepare("SELECT * FROM test;")->Execute();

	int32_t actualValue = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		actualValue = row->getAsInt32(0);
	});

	EXPECT_EQ(actualValue, expectValue);
}

TEST_F(SqlitePreparedStatementTest, Bind_uint32){
	sqlite->Execute("CREATE TABLE test (value INTEGER);");

	shared_ptr<PreparedExecutionInterface> prepared = sqlite->Prepare("INSERT INTO test VALUES (?1)");

	u_int32_t expectValue = 123;

	prepared->Bind(1, expectValue);
	prepared->Execute();

	shared_ptr<ResultInterface> result = sqlite->Prepare("SELECT * FROM test;")->Execute();

	u_int32_t actualValue = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		actualValue = row->getAsUint32(0);
	});

	EXPECT_EQ(actualValue, expectValue);
}

TEST_F(SqlitePreparedStatementTest, Bind_int64){
	sqlite->Execute("CREATE TABLE test (value INTEGER);");

	shared_ptr<PreparedExecutionInterface> prepared = sqlite->Prepare("INSERT INTO test VALUES (?1)");

	int64_t expectValue = 123;

	prepared->Bind(1, expectValue);
	prepared->Execute();

	shared_ptr<ResultInterface> result = sqlite->Prepare("SELECT * FROM test;")->Execute();

	int64_t actualValue = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		actualValue = row->getAsInt64(0);
	});

	EXPECT_EQ(actualValue, expectValue);
}

TEST_F(SqlitePreparedStatementTest, Bind_uint64){
	sqlite->Execute("CREATE TABLE test (value INTEGER);");

	shared_ptr<PreparedExecutionInterface> prepared = sqlite->Prepare("INSERT INTO test VALUES (?1)");

	u_int64_t expectValue = 123;

	EXPECT_THROW({
		prepared->Bind(1, expectValue);
	}, SqliteException);

}

TEST_F(SqlitePreparedStatementTest, Bind_double){
	sqlite->Execute("CREATE TABLE test (value DOUBLE);");

	shared_ptr<PreparedExecutionInterface> prepared = sqlite->Prepare("INSERT INTO test VALUES (?1)");

	double expectValue = 123.123;

	prepared->Bind(1, expectValue);
	prepared->Execute();

	shared_ptr<ResultInterface> result = sqlite->Prepare("SELECT * FROM test;")->Execute();

	double actualValue = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		actualValue = row->getAsDouble(0);
	});

	EXPECT_EQ(actualValue, expectValue);
}

TEST_F(SqlitePreparedStatementTest, Bind_string){
	sqlite->Execute("CREATE TABLE test (value STRING);");

	shared_ptr<PreparedExecutionInterface> prepared = sqlite->Prepare("INSERT INTO test VALUES (?1)");

	string expectValue = "ABCDEF";

	prepared->Bind(1, expectValue);
	prepared->Execute();

	shared_ptr<ResultInterface> result = sqlite->Prepare("SELECT * FROM test;")->Execute();

	string actualValue;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		actualValue = row->getAsString(0);
	});

	EXPECT_EQ(actualValue, expectValue);
}

TEST_F(SqlitePreparedStatementTest, Bind_stringToBlob){
	sqlite->Execute("CREATE TABLE test (value BLOB);");

	shared_ptr<PreparedExecutionInterface> prepared = sqlite->Prepare("INSERT INTO test VALUES (?1)");

	string expectValue = "ABCDEF";

	prepared->Bind(1, expectValue);
	prepared->Execute();

	shared_ptr<ResultInterface> result = sqlite->Prepare("SELECT * FROM test;")->Execute();

	string actualValue;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		actualValue = row->getAsString(0);
	});

	EXPECT_EQ(actualValue, expectValue);
}

}}}
