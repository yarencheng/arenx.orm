

#pragma once

#include <string>

namespace arenx { namespace orm {

class ResultRowInterface{

public:

	virtual ~ResultRowInterface () = default;

	virtual int getAsInt() = 0;
	virtual std::string getAsString() = 0;

};

}}
