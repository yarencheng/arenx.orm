

#pragma once

namespace arenx {
namespace orm {

template<class PERSISTENCE>
class Persistent{

public:

	Persistent(PERSISTENCE& p){
		pointer = &p;
	}

	Persistent<PERSISTENCE>& named(std::string s){
		name = s;
		return *this;
	}

	std::string name;
	PERSISTENCE* pointer;
};

}
}
