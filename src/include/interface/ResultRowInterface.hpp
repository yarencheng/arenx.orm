

#pragma once

#include <string>
#include <vector>

namespace arenx { namespace orm {

class ResultRowInterface{

public:

	virtual ~ResultRowInterface () = default;

	virtual int32_t getAsInt32(const std::size_t& index) = 0;
	virtual int32_t getAsInt32(const std::string& property) = 0;
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

	virtual std::vector<std::string> GetValues() = 0;
};

}}
