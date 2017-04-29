
#include <boost/lexical_cast.hpp>
#include "Persistent.hpp"

#pragma once

namespace arenx { namespace orm {

class PersistentAdaptorInterface{

public:

	enum class Mode{
		UNKNOWN, READ, WRITE
	};

	virtual ~PersistentAdaptorInterface () = default;

	template<class PERSISTENCE>
	PersistentAdaptorInterface& operator|(Persistent<PERSISTENCE>& p) {
		using namespace std;

		switch (_mode) {
		case Mode::WRITE:
			if (typeid(int) == typeid(PERSISTENCE)) {
				int i = boost::lexical_cast<int>(*p.getPointer());
				save(p.getName(), i);
			} else if (typeid(string) == typeid(PERSISTENCE)) {
				string s = boost::lexical_cast<string>(*p.getPointer());
				save(p.getName(), s);
			}
			break;
		case Mode::READ:
			if (typeid(int) == typeid(PERSISTENCE)) {
				load(p.getName(), *(int*)p.getPointer());
			} else if (typeid(string) == typeid(PERSISTENCE)) {
				load(p.getName(), *(string*)p.getPointer());
			}
			break;
		default:
			break;
		}

		return *this;
	}

	template<class KEY>
	void read(const KEY& key){
		using namespace std;

		_mode = Mode::READ;
		if (typeid(int) == typeid(KEY)) {
			int i = boost::lexical_cast<int>(key);
			setKey(i);
		} else if (typeid(string) == typeid(KEY)) {
			string s = boost::lexical_cast<string>(key);
			setKey(s);
		}
	}

	virtual void write(){ _mode = Mode::WRITE; }
	virtual void execute() = 0;

protected:
//	virtual Mode getMode() = 0;
	virtual void save(const std::string& name, int i) = 0;
	virtual void save(const std::string& name, const std::string& s) = 0;

	virtual void setKey(int i) = 0;
	virtual void setKey(const std::string& s) = 0;

	virtual void load(const std::string& name, int& i) = 0;
	virtual void load(const std::string& name, std::string& s) = 0;


private:
	Mode _mode;

};

}}
