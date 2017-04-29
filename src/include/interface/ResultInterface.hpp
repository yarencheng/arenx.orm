

#pragma once

#include <memory>
#include <functional>
#include "ResultRowInterface.hpp"

namespace arenx { namespace orm {

class ResultInterface{

public:

	virtual ~ResultInterface () = default;

	virtual void forEach(const std::function<void(std::shared_ptr<ResultRowInterface>)>& fn) = 0;
};

}}
