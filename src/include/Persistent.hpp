

#pragma once

namespace arenx {
namespace orm {

template<class PERSISTENCE>
class Persistent{

public:

	Persistent(PERSISTENCE& p){
		_pointer = &p;
	}

	Persistent<PERSISTENCE>& named(const std::string& name){
		_name = name;
		return *this;
	}

	std::string getName(){
		return _name;
	}

	PERSISTENCE* getPointer(){
		return _pointer;
	}

private:
	std::string _name;
	PERSISTENCE* _pointer;
};

}
}
