/*
 * ValidatorTest.cpp
 *
 *  Created on: 2017年4月30日
 *      Author: arenx
 */

#include "utils/Validator.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::std;
using namespace ::testing;
using namespace ::arenx::orm;


using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;

namespace arenx { namespace orm { namespace ValidatorTest {

class ValidatorTest  : public Test {
protected:

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(ValidatorTest, VALIDATE_NOT_NULL_true){
	shared_ptr<int> ptr = make_shared<int>(123);

	EXPECT_NO_THROW({
		VALIDATE_NOT_NULL(ptr, "");
	});
}

TEST_F(ValidatorTest, VALIDATE_NOT_NULL_fals){
	shared_ptr<int> ptr;

	EXPECT_THROW({
		VALIDATE_NOT_NULL(ptr, "");
	}, IllegalArgumentException);
}

}}}


