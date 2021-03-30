#pragma once

#include <utility>

template <typename F>
class FinalAction {
public:
	FinalAction(F f) : f_{ f } {}
	~FinalAction() { f_(); }
private:
	F f_;
};

template <class F>
FinalAction<F> Finally(F f) {
	return FinalAction<F>(f);
}