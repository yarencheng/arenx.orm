

#pragma once

namespace arenx { namespace orm {

class PersistentAdaptorInterface{

public:

	enum class Mode{
		READ, WRITE
	};

//	template<class PERSISTENCE>
//	PersistentAdaptorInterface& operator|(Persistent<PERSISTENCE>& p) {
//
//
//	}

	void setMode(const Mode& mode){
		_mode = mode;
	}

protected:


private:
	Mode _mode;

};

}}
