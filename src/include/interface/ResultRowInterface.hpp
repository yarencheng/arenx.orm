

#pragma once

#include <string>

namespace arenx { namespace orm {

class ResultRowInterface{

public:

	virtual ~ResultRowInterface () = default;

	virtual int getAsInt(const std::size_t& index) = 0;
	virtual int getAsInt(const std::string& property) = 0;
	virtual uint32_t getAsUint32(const std::size_t& index) = 0;
	virtual uint32_t getAsUint32(const std::string& property) = 0;
	virtual int64_t getAsInt64(const std::size_t& index) = 0;
	virtual int64_t getAsInt64(const std::string& property) = 0;
	virtual uint64_t getAsUint64(const std::size_t& index) = 0;
	virtual uint64_t getAsUint64(const std::string& property) = 0;
	virtual double getAsDouble(const std::size_t& index) = 0;
	virtual double getAsDouble(const std::string& property) = 0;
	virtual std::string getAsString(const std::size_t& index) = 0;
	virtual std::string getAsString(const std::string& property) = 0;

};

}}
