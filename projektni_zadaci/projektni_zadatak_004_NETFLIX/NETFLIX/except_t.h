#pragma once

#include <stdexcept>
#include <string>

class except_t : public std::exception {
public:
	except_t(const char* msg) noexcept : 
		msg_{ std::string{ base }.append(msg) } {
	}
	virtual ~except_t() = default;
	virtual const char* what() const noexcept override { return msg_.c_str(); };
	
protected:
	std::string msg_;

private:
	static constexpr const char* base{ "EXCEPT::" };

};
