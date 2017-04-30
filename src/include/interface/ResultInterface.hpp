

#pragma once

#include <memory>
#include <functional>
#include <iostream>
#include "ResultRowInterface.hpp"

namespace arenx { namespace orm {

class ResultInterface{

public:

	virtual ~ResultInterface () = default;

	virtual void forEach(const std::function<void(std::shared_ptr<ResultRowInterface>)>& fn) = 0;

protected:
	virtual std::ostream& dump(std::ostream& os) = 0;

private:
	friend std::ostream& operator<<(std::ostream& os, ResultInterface& result){
		return result.dump(os);
	}
};

}}
