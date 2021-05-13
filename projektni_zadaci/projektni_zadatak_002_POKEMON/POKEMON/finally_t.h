#pragma once

#include <utility>

template <typename F>
class final_action_t {
public:
	final_action_t(F f) : f_{ f } {}
	~final_action_t() { f_(); }
private:
	F f_;
};

template <class F>
final_action_t<F> finally_t(F f) {
	return final_action_t<F>(f);
}