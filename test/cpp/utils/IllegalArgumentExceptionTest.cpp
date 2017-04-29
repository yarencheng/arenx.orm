
#include "utils/IllegalArgumentException.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::std;
using namespace ::testing;
using namespace ::arenx::orm;


using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;

namespace arenx { namespace orm { namespace IllegalArgumentExceptionTest {

class IllegalArgumentExceptionTest  : public Test {
protected:

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(IllegalArgumentExceptionTest, macroDefine_0arg){

	IllegalArgumentException ex = ILLEGAL_ARGUMENT_EXCEPTION(); int expectLine = __LINE__; string expectFile = __FILE__;

	EXPECT_THAT(ex.GetMessage(), HasSubstr(to_string(expectLine)));
	EXPECT_THAT(ex.GetMessage(), HasSubstr(expectFile));
}

TEST_F(IllegalArgumentExceptionTest, macroDefine_1arg_string){

	string expectMessage = "ABCDabcd";
	IllegalArgumentException ex = ILLEGAL_ARGUMENT_EXCEPTION(expectMessage); int expectLine = __LINE__; string expectFile = __FILE__;

	EXPECT_THAT(ex.GetMessage(), HasSubstr(expectMessage));
	EXPECT_THAT(ex.GetMessage(), HasSubstr(to_string(expectLine)));
	EXPECT_THAT(ex.GetMessage(), HasSubstr(expectFile));
}

TEST_F(IllegalArgumentExceptionTest, macroDefine_1arg_IllegalArgumentException){

	string expectMessage1 = "abcdefg";
	IllegalArgumentException ex1 = ILLEGAL_ARGUMENT_EXCEPTION(expectMessage1); int expectLine1 = __LINE__; string expectFile1 = __FILE__;

	IllegalArgumentException ex2 = ILLEGAL_ARGUMENT_EXCEPTION(ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine1)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(IllegalArgumentExceptionTest, macroDefine_1arg_stdException){

	string expectMessage1 = "abcdefg";
	runtime_error ex1 = runtime_error(expectMessage1);

	IllegalArgumentException ex2 = ILLEGAL_ARGUMENT_EXCEPTION(ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(IllegalArgumentExceptionTest, macroDefine_2arg_string_IllegalArgumentException){

	string expectMessage1 = "abcdefg";
	IllegalArgumentException ex1 = ILLEGAL_ARGUMENT_EXCEPTION(expectMessage1); int expectLine1 = __LINE__; string expectFile1 = __FILE__;

	string expectMessage2 = "ABCDEFG";
	IllegalArgumentException ex2 = ILLEGAL_ARGUMENT_EXCEPTION(expectMessage2, ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage2));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine1)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(IllegalArgumentExceptionTest, macroDefine_2arg_string_stdException){

	string expectMessage1 = "abcdefg";
	runtime_error ex1 = runtime_error(expectMessage1);

	string expectMessage2 = "ABCDEFG";
	IllegalArgumentException ex2 = ILLEGAL_ARGUMENT_EXCEPTION(expectMessage2, ex1); int expectLine2 = __LINE__; string expectFile2 = __FILE__;

	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage1));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectMessage2));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(to_string(expectLine2)));
	EXPECT_THAT(ex2.GetMessage(), HasSubstr(expectFile2));
}

TEST_F(IllegalArgumentExceptionTest, GetName){

	IllegalArgumentException ex = ILLEGAL_ARGUMENT_EXCEPTION();

	EXPECT_EQ(ex.GetName(), "IllegalArgumentException");
}


}}}
