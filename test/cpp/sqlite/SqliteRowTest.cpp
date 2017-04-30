/*
 * SqliteDatastoreTest.cpp
 *
 *  Created on: 2017年4月23日
 *      Author: arenx
 */

#include "sqlite/SqliteResult.hpp"
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

namespace arenx { namespace orm { namespace SqliteRowTest {

class SqliteRowTest  : public Test {
protected:

	shared_ptr<SqliteDatastore> sqlite;

	virtual void SetUp() {
		sqlite = make_shared<SqliteDatastore>(":memory:");
	}

	virtual void TearDown() {
		sqlite = nullptr;
	}
};

TEST_F(SqliteRowTest, getAsInt32_by_name){

	sqlite->Execute("CREATE TABLE test (v0 INTEGER);");
	sqlite->Execute("INSERT INTO test VALUES (111)");

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsInt32("v0"), 111);
		EXPECT_THROW({row->getAsInt32("xxx");}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
}

TEST_F(SqliteRowTest, getAsUint32_by_name){

	sqlite->Execute("CREATE TABLE test (v0 INTEGER);");
	sqlite->Execute("INSERT INTO test VALUES (111)");

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsUint32("v0"), (uint32_t)111);
		EXPECT_THROW({row->getAsUint32("xxx");}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
}

TEST_F(SqliteRowTest, getAsInt64_by_name){

	sqlite->Execute("CREATE TABLE test (v0 INTEGER);");
	sqlite->Execute("INSERT INTO test VALUES (111)");

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsInt64("v0"), 111);
		EXPECT_THROW({row->getAsInt64("xxx");}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
}

TEST_F(SqliteRowTest, getAsUint64_by_name){

	sqlite->Execute("CREATE TABLE test (v0 INTEGER);");
	sqlite->Execute("INSERT INTO test VALUES (111)");

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsUint64("v0"), (uint64_t)111);
		EXPECT_THROW({row->getAsUint64("xxx");}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
}

TEST_F(SqliteRowTest, getAsDouble_by_name){

	sqlite->Execute("CREATE TABLE test (v0 INTEGER);");
	sqlite->Execute("INSERT INTO test VALUES (111.111)");

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsDouble("v0"), 111.111);
		EXPECT_THROW({row->getAsDouble("xxx");}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
}

TEST_F(SqliteRowTest, getAsString_by_name){

	sqlite->Execute("CREATE TABLE test (v0 INTEGER);");
	sqlite->Execute("INSERT INTO test VALUES ('ABC')");

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsString("v0"), "ABC");
		EXPECT_THROW({row->getAsString("xxx");}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
}

TEST_F(SqliteRowTest, getAsInt32_by_index){

	int columeCount = 0;

	stringstream create;
	create << "CREATE TABLE test (";
	// valid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " BLOB,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " NUMERIC,"; columeCount++;
	// invalid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " FLOAT,"; columeCount++;
	create << "v" << (columeCount) << " NUMERIC,"; columeCount++;
	create << "v" << (columeCount) << " BLOB"; columeCount++;
	create << ");";

	sqlite->Execute(create.str());

	stringstream insert;
	insert << "INSERT INTO test VALUES (";
	// valid
	insert << numeric_limits<int32_t>::min() << ",";
	insert << "-1" << ",";
	insert << "0" << ",";
	insert << "1" << ",";
	insert << numeric_limits<int32_t>::max() << ",";
	insert << "0x0A0B0C0D" << ",";
	insert << "'333'" << ",";
	insert << "444" << ",";
	// invalid
	insert << "NULL" << ",";
	insert << "'not int'" << ",";
	insert << "222.222" << ",";
	insert << "0x1122334455667788" << ",";
	insert << "x'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'";
	insert << ")";

	sqlite->Execute(insert.str());

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;
	int indexCount = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsInt32(indexCount++), numeric_limits<int32_t>::min());
		EXPECT_EQ(row->getAsInt32(indexCount++), -1);
		EXPECT_EQ(row->getAsInt32(indexCount++), 0);
		EXPECT_EQ(row->getAsInt32(indexCount++), 1);
		EXPECT_EQ(row->getAsInt32(indexCount++), numeric_limits<int32_t>::max());
		EXPECT_EQ(row->getAsInt32(indexCount++), 0x0A0B0C0D);
		EXPECT_EQ(row->getAsInt32(indexCount++), 333);
		EXPECT_EQ(row->getAsInt32(indexCount++), 444);

		EXPECT_THROW({row->getAsInt32(indexCount++);}, SqliteException);
		EXPECT_THROW({row->getAsInt32(indexCount++);}, SqliteException);
		EXPECT_EQ(row->getAsInt32(indexCount++), 222);
		EXPECT_EQ(row->getAsInt32(indexCount++), (int32_t)0x1122334455667788);
		EXPECT_THROW({row->getAsInt32(indexCount++);}, SqliteException);

		EXPECT_THROW({row->getAsInt32(999);}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
	EXPECT_EQ(indexCount, columeCount);
}


TEST_F(SqliteRowTest, getAsUint32_by_index){

	int columeCount = 0;

	stringstream create;
	create << "CREATE TABLE test (";
	// valid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " BLOB,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " NUMERIC,"; columeCount++;
	// invalid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " FLOAT,"; columeCount++;
	create << "v" << (columeCount) << " NUMERIC,"; columeCount++;
	create << "v" << (columeCount) << " BLOB"; columeCount++;
	create << ");";

	sqlite->Execute(create.str());

	stringstream insert;
	insert << "INSERT INTO test VALUES (";
	// valid
	insert << numeric_limits<uint32_t>::min() << ",";
	insert << "1" << ",";
	insert << numeric_limits<uint32_t>::max() << ",";
	insert << "0x0A0B0C0D" << ",";
	insert << "'333'" << ",";
	insert << "444" << ",";
	// invalid
	insert << "NULL" << ",";
	insert << "'not int'" << ",";
	insert << "222.222" << ",";
	insert << "0x1122334455667788" << ",";
	insert << "x'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'";
	insert << ")";

	sqlite->Execute(insert.str());

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;
	int indexCount = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsUint32(indexCount++), numeric_limits<uint32_t>::min());
		EXPECT_EQ(row->getAsUint32(indexCount++), (uint32_t)1);
		EXPECT_EQ(row->getAsUint32(indexCount++), numeric_limits<uint32_t>::max());
		EXPECT_EQ(row->getAsUint32(indexCount++), (uint32_t)0x0A0B0C0D);
		EXPECT_EQ(row->getAsUint32(indexCount++), (uint32_t)333);
		EXPECT_EQ(row->getAsUint32(indexCount++), (uint32_t)444);

		EXPECT_THROW({row->getAsUint32(indexCount++);}, SqliteException);
		EXPECT_THROW({row->getAsUint32(indexCount++);}, SqliteException);
		EXPECT_EQ(row->getAsUint32(indexCount++), (uint32_t)222);
		EXPECT_EQ(row->getAsUint32(indexCount++), (uint32_t)0x1122334455667788);
		EXPECT_THROW({row->getAsUint32(indexCount++);}, SqliteException);

		EXPECT_THROW({row->getAsUint32(999);}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
	EXPECT_EQ(indexCount, columeCount);
}

TEST_F(SqliteRowTest, getAsInt64_by_index){

	int columeCount = 0;

	stringstream create;
	create << "CREATE TABLE test (";
	// valid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " BLOB,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " NUMERIC,"; columeCount++;
	// invalid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " FLOAT,"; columeCount++;
	create << "v" << (columeCount) << " BLOB"; columeCount++;
	create << ");";

	sqlite->Execute(create.str());

	stringstream insert;
	insert << "INSERT INTO test VALUES (";
	// valid
	insert << numeric_limits<int64_t>::min() << ",";
	insert << "-1" << ",";
	insert << "0" << ",";
	insert << "1" << ",";
	insert << numeric_limits<int64_t>::max() << ",";
	insert << "0x0A0B0C0D" << ",";
	insert << "'333'" << ",";
	insert << "444" << ",";
	// invalid
	insert << "NULL" << ",";
	insert << "'not int'" << ",";
	insert << "222.222" << ",";
	insert << "x'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'";
	insert << ")";

	sqlite->Execute(insert.str());

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;
	int indexCount = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsInt64(indexCount++), numeric_limits<int64_t>::min());
		EXPECT_EQ(row->getAsInt64(indexCount++), -1);
		EXPECT_EQ(row->getAsInt64(indexCount++), 0);
		EXPECT_EQ(row->getAsInt64(indexCount++), 1);
		EXPECT_EQ(row->getAsInt64(indexCount++), numeric_limits<int64_t>::max());
		EXPECT_EQ(row->getAsInt64(indexCount++), 0x0A0B0C0D);
		EXPECT_EQ(row->getAsInt64(indexCount++), 333);
		EXPECT_EQ(row->getAsInt64(indexCount++), 444);

		EXPECT_THROW({row->getAsInt64(indexCount++);}, SqliteException);
		EXPECT_THROW({row->getAsInt64(indexCount++);}, SqliteException);
		EXPECT_EQ(row->getAsInt64(indexCount++), (int64_t)222);
		EXPECT_THROW({row->getAsInt64(indexCount++);}, SqliteException);

		EXPECT_THROW({row->getAsInt64(999);}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
	EXPECT_EQ(indexCount, columeCount);
}


TEST_F(SqliteRowTest, getAsUint64_by_index){

	int columeCount = 0;

	stringstream create;
	create << "CREATE TABLE test (";
	// valid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " BLOB,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " NUMERIC,"; columeCount++;
	// invalid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " FLOAT,"; columeCount++;
	create << "v" << (columeCount) << " BLOB"; columeCount++;
	create << ");";

	sqlite->Execute(create.str());

	stringstream insert;
	insert << "INSERT INTO test VALUES (";
	// valid
	insert << numeric_limits<uint64_t>::min() << ",";
	insert << "1" << ",";
	insert << numeric_limits<uint64_t>::max() << ",";
	insert << "0x0A0B0C0D" << ",";
	insert << "'333'" << ",";
	insert << "444" << ",";
	// invalid
	insert << "NULL" << ",";
	insert << "'not int'" << ",";
	insert << "222.222" << ",";
	insert << "x'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'";
	insert << ")";

	sqlite->Execute(insert.str());

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;
	int indexCount = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_EQ(row->getAsUint64(indexCount++), numeric_limits<uint64_t>::min());
		EXPECT_EQ(row->getAsUint64(indexCount++), (uint64_t)1);
		EXPECT_EQ(row->getAsUint64(indexCount++), (uint64_t)0);
		EXPECT_EQ(row->getAsUint64(indexCount++), (uint64_t)0x0A0B0C0D);
		EXPECT_EQ(row->getAsUint64(indexCount++), (uint64_t)333);
		EXPECT_EQ(row->getAsUint64(indexCount++), (uint64_t)444);

		EXPECT_THROW({row->getAsUint64(indexCount++);}, SqliteException);
		EXPECT_THROW({row->getAsUint64(indexCount++);}, SqliteException);
		EXPECT_EQ(row->getAsUint64(indexCount++), (uint64_t)222);
		EXPECT_THROW({row->getAsUint64(indexCount++);}, SqliteException);

		EXPECT_THROW({row->getAsUint64(999);}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
	EXPECT_EQ(indexCount, columeCount);
}

TEST_F(SqliteRowTest, getAsDouble_by_index){

	int columeCount = 0;

	stringstream create;
	create << "CREATE TABLE test (";
	// valid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " BLOB,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " NUMERIC,"; columeCount++;
	// invalid
	create << "v" << (columeCount) << " INTEGER,"; columeCount++;
	create << "v" << (columeCount) << " TEXT,"; columeCount++;
	create << "v" << (columeCount) << " BLOB"; columeCount++;
	create << ");";

	sqlite->Execute(create.str());

	stringstream insert;
	insert << "INSERT INTO test VALUES (";
	// valid
	insert << numeric_limits<double>::min() << ",";
	insert << "-1" << ",";
	insert << "0" << ",";
	insert << "1" << ",";
	insert << numeric_limits<double>::max() << ",";
	insert << "0x0A0B0C0D" << ",";
	insert << "'333'" << ",";
	insert << "444" << ",";
	// invalid
	insert << "NULL" << ",";
	insert << "'not int'" << ",";
	insert << "x'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'";
	insert << ")";

	sqlite->Execute(insert.str());

	shared_ptr<ResultInterface> result = sqlite->Execute("SELECT * FROM test;");

	int count = 0;
	int indexCount = 0;

	result->forEach([&](shared_ptr<ResultRowInterface> row){
		count++;

		EXPECT_NEAR(row->getAsDouble(indexCount++), numeric_limits<double>::min(), 0.0001);
		EXPECT_DOUBLE_EQ(row->getAsDouble(indexCount++), -1);
		EXPECT_DOUBLE_EQ(row->getAsDouble(indexCount++), 0);
		EXPECT_DOUBLE_EQ(row->getAsDouble(indexCount++), 1);
		EXPECT_GE(row->getAsDouble(indexCount++), 1.0e+308);
		EXPECT_DOUBLE_EQ(row->getAsDouble(indexCount++), (double)0x0A0B0C0D);
		EXPECT_DOUBLE_EQ(row->getAsDouble(indexCount++), (double)333);
		EXPECT_DOUBLE_EQ(row->getAsDouble(indexCount++), (double)444);

		EXPECT_THROW({row->getAsDouble(indexCount++);}, SqliteException);
		EXPECT_THROW({row->getAsDouble(indexCount++);}, SqliteException);
		EXPECT_THROW({row->getAsDouble(indexCount++);}, SqliteException);

		EXPECT_THROW({row->getAsDouble(999);}, IllegalArgumentException);
	});

	EXPECT_EQ(count, 1);
	EXPECT_EQ(indexCount, columeCount);
}

}}}
