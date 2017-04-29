
#include <iostream>
#include "interface/PersistentAdaptorInterface.hpp"

#pragma once

namespace arenx { namespace orm {

class DummyPersistentAdaptor: public PersistentAdaptorInterface{

public:

	virtual ~DummyPersistentAdaptor () = default;

//	virtual void write(){ _mode = Mode::WRITE; }
	virtual void execute(){};

protected:
//	virtual Mode getMode() { return _mode; };

private:
//	Mode _mode;
	virtual void save(const std::string& name, int i) {
		using namespace std;
		cout << "DummyPersistentAdaptor::save(" << name << ", int(" << i << ") )" << endl;
	};
	virtual void save(const std::string& name, const std::string& s) {
		using namespace std;
		cout << "DummyPersistentAdaptor::save(" << name << ", string(" << s << ") )" << endl;
	};

	virtual void setKey(int i){
		using namespace std;
		cout << "DummyPersistentAdaptor::setKey( int(" << i << ") )" << endl;
	}

	virtual void setKey(const std::string& s){
		using namespace std;
		cout << "DummyPersistentAdaptor::setKey( string(" << s << ") )" << endl;
	}

	virtual void load(const std::string& name, int& i) {
		using namespace std;
		i = 789;
		cout << "DummyPersistentAdaptor::load(" << name << ", int(" << i << ") )" << endl;
	};
	virtual void load(const std::string& name, std::string& s) {
		using namespace std;
		s = "XYZ";
		cout << "DummyPersistentAdaptor::load(" << name << ", string(" << s << ") )" << endl;
	};
};

}}
