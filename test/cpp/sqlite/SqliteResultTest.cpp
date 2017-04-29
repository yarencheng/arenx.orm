/*
 * SqliteDatastoreTest.cpp
 *
 *  Created on: 2017年4月23日
 *      Author: arenx
 */

#include "sqlite/SqliteResult.hpp"
#include "sqlite/SqliteDatastore.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::std;
using namespace ::testing;
using namespace ::arenx::orm;


using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;

namespace arenx { namespace orm { namespace SqliteResultTest {

class SqliteResultTest  : public Test {
protected:

	shared_ptr<SqliteDatastore> sqlite;

	virtual void SetUp() {
		sqlite = make_shared<SqliteDatastore>(":memory:");
	}

	virtual void TearDown() {
		sqlite = nullptr;
	}
};

TEST_F(SqliteResultTest, forEach_0){

	sqlite->Execute("CREATE TABLE test (value int);");

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;
	});

	EXPECT_EQ(count, 0);
}

TEST_F(SqliteResultTest, forEach_1){

	sqlite->Execute("CREATE TABLE test (value int);");
	sqlite->Execute("INSERT INTO test VALUES (1);");

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;
	});

	EXPECT_EQ(count, 1);
}

TEST_F(SqliteResultTest, forEach_2){

	sqlite->Execute("CREATE TABLE test (value int);");
	sqlite->Execute("INSERT INTO test VALUES (1), (2);");

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;
	});

	EXPECT_EQ(count, 2);
}


}}}
