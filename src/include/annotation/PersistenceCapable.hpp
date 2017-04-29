

#pragma once

namespace arenx {
namespace orm {

class PersistenceCapable{

public:

	PersistenceCapable& named(const std::string& name){
		_name = name;
		return *this;
	}

	std::string getName(){
		return _name;
	}

private:
	std::string _name;
};

}
}
