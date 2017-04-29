/*
 * HelloWorldTest.cpp
 *
 *  Created on: 2017年4月23日
 *      Author: arenx
 */

#include "sqlite/SqliteException.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::std;
using namespace ::testing;
using namespace ::arenx::orm;


using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;

namespace arenx { namespace orm { namespace SqliteExceptionTest {

class SqliteExceptionTest  : public Test {
protected:

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(SqliteExceptionTest, macroDefine_0arg){

	SqliteException ex = SQLITE_EXCEPTION(); int expectLine = __LINE__; string expectFile = __FILE__;

	EXPECT_THAT(ex.GetMessage(), HasSubstr(to_string(expectLine)));
	EXPECT_THAT(ex.GetMessage(), HasSubstr(expectFile));
}

TEST_F(SqliteExceptionTest, macroDefine_1arg_string){

	string expectMessage = "ABCDabcd";
	SqliteException ex = SQLITE_EXCEPTION(expectMessage); int expectLine = __LINE__; string expectFile = __FILE__;

	EXPECT_THAT(ex.GetMessage(), HasSubstr(expectMessage));
	EXPECT_THAT(ex.GetMessage(), HasSubstr(to_string(expectLine)));
	EXPECT_THAT(ex.GetMessage(), HasSubstr(expectFile));
}

TEST_F(SqliteExceptionTest, macroDefine_1arg_SqliteException){

	string expectMessage1 = "abcdefg";
	SqliteException ex1 = SQLITE_EXCEPTION(expectMessage1); int expectLine1 = __LINE__; string expectFile1 = __FILE__;

	SqliteException ex2 = SQLITE_EXCEPTION(ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine1)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(SqliteExceptionTest, macroDefine_1arg_stdException){

	string expectMessage1 = "abcdefg";
	runtime_error ex1 = runtime_error(expectMessage1);

	SqliteException ex2 = SQLITE_EXCEPTION(ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(SqliteExceptionTest, macroDefine_2arg_string_SqliteException){

	string expectMessage1 = "abcdefg";
	SqliteException ex1 = SQLITE_EXCEPTION(expectMessage1); int expectLine1 = __LINE__; string expectFile1 = __FILE__;

	string expectMessage2 = "ABCDEFG";
	SqliteException ex2 = SQLITE_EXCEPTION(expectMessage2, ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage2));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine1)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(SqliteExceptionTest, macroDefine_2arg_string_stdException){

	string expectMessage1 = "abcdefg";
	runtime_error ex1 = runtime_error(expectMessage1);

	string expectMessage2 = "ABCDEFG";
	SqliteException ex2 = SQLITE_EXCEPTION(expectMessage2, ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage2));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(SqliteExceptionTest, GetName){

	SqliteException ex = SQLITE_EXCEPTION();

	EXPECT_EQ(ex.GetName(), "SqliteException");
}


}}}
