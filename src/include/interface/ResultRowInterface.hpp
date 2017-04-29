

#pragma once

#include <string>

namespace arenx { namespace orm {

class ResultRowInterface{

public:

	virtual ~ResultRowInterface () = default;

	virtual int GetAsInt() = 0;
	virtual std::string GetAsString() = 0;

};

}}
