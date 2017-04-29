/*
 * HelloWorldTest.cpp
 *
 *  Created on: 2017年4月23日
 *      Author: arenx
 */

#include "OrmException.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::std;
using namespace ::testing;
using namespace ::arenx::orm;


using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;

namespace arenx { namespace orm { namespace OrmExceptionTest {

class OrmExceptionTest  : public Test {
protected:

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(OrmExceptionTest, macroDefine_0arg){

	OrmException ex = ORM_EXCEPTION(); int expectLine = __LINE__; string expectFile = __FILE__;

	EXPECT_THAT(ex.GetMessage(), HasSubstr(to_string(expectLine)));
	EXPECT_THAT(ex.GetMessage(), HasSubstr(expectFile));
}

TEST_F(OrmExceptionTest, macroDefine_1arg_string){

	string expectMessage = "ABCDabcd";
	OrmException ex = ORM_EXCEPTION(expectMessage); int expectLine = __LINE__; string expectFile = __FILE__;

	EXPECT_THAT(ex.GetMessage(), HasSubstr(expectMessage));
	EXPECT_THAT(ex.GetMessage(), HasSubstr(to_string(expectLine)));
	EXPECT_THAT(ex.GetMessage(), HasSubstr(expectFile));
}

TEST_F(OrmExceptionTest, macroDefine_1arg_OrmException){

	string expectMessage1 = "abcdefg";
	OrmException ex1 = ORM_EXCEPTION(expectMessage1); int expectLine1 = __LINE__; string expectFile1 = __FILE__;

	OrmException ex2 = ORM_EXCEPTION(ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine1)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(OrmExceptionTest, macroDefine_1arg_stdException){

	string expectMessage1 = "abcdefg";
	runtime_error ex1 = runtime_error(expectMessage1);

	OrmException ex2 = ORM_EXCEPTION(ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(OrmExceptionTest, macroDefine_2arg_string_OrmException){

	string expectMessage1 = "abcdefg";
	OrmException ex1 = ORM_EXCEPTION(expectMessage1); int expectLine1 = __LINE__; string expectFile1 = __FILE__;

	string expectMessage2 = "ABCDEFG";
	OrmException ex2 = ORM_EXCEPTION(expectMessage2, ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage2));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine1)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(OrmExceptionTest, macroDefine_2arg_string_stdException){

	string expectMessage1 = "abcdefg";
	runtime_error ex1 = runtime_error(expectMessage1);

	string expectMessage2 = "ABCDEFG";
	OrmException ex2 = ORM_EXCEPTION(expectMessage2, ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage2));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(OrmExceptionTest, GetStackTrace){

	OrmException ex = ORM_EXCEPTION();

	cout << ex.GetStackTrace();
}

TEST_F(OrmExceptionTest, GetName){

	OrmException ex = ORM_EXCEPTION();

	EXPECT_EQ(ex.GetName(), "OrmException");
}


}}}
