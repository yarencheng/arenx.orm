/*
 * SqliteDatastoreTest.cpp
 *
 *  Created on: 2017年4月23日
 *      Author: arenx
 */

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

namespace arenx { namespace orm { namespace SqliteDatastoreTest {

class SqliteDatastoreTest  : public Test {
protected:

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(SqliteDatastoreTest, constructor){
	SqliteDatastore sqlite(":memory:");
}

TEST_F(SqliteDatastoreTest, Execute_success){
	SqliteDatastore sqlite(":memory:");
	sqlite.Execute("CREATE TABLE testttt (value STRING);");
}

TEST_F(SqliteDatastoreTest, Execute_fail){
	SqliteDatastore sqlite(":memory:");

	EXPECT_THROW({
		sqlite.Execute("CREATE TABLEeeeeeee testttt (value STRING);");
	}, SqliteException);

}



}}}
