
#include "SimplePersistentManager.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::std;
using namespace ::testing;

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;

namespace arenx { namespace orm { namespace SimplePersistentManagerTest {

class SimplePersistentManagerTest  : public Test {
protected:

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};


TEST_F(SimplePersistentManagerTest, hello){

	SimplePersistentManager pm;
	DummyDatastore ds;
}



}}}
