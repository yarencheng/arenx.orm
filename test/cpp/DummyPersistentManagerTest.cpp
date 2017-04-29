
#include "DummyPersistentManager.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::std;
using namespace ::testing;

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;

namespace arenx { namespace orm { namespace DummyPersistentManagerTest {

class DummyPersistentManagerTest  : public Test {
protected:

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

class DummyDAO{
public:

	int _i;
	string _s;

	template<class ADAPTOR>
	void adapt(ADAPTOR& adaptor) {
		adaptor
			| PersistenceCapable().named("tableeeee")
			| Persistent<int>(_i).named("_i")
			| Persistent<string>(_s).named("_s")
			;
	}
};


TEST_F(DummyPersistentManagerTest, ssssssssss){

	shared_ptr<DummyPersistentManager> pm = make_shared<DummyPersistentManager>();
	DummyDAO dao = {123, "ABCD"};

	pm->makePersist(dao);
}

TEST_F(DummyPersistentManagerTest, sdsdsd){

	shared_ptr<DummyPersistentManager> pm = make_shared<DummyPersistentManager>();

	DummyDAO dao = pm->getObjectById<DummyDAO>(999);

	cout << "dao._i = " << dao._i << endl;
	cout << "dao._s = " << dao._s << endl;
}



}}}
