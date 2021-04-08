#include <iostream>
#include "Vector.h"
#include "Vector2i.h"
#include <string>

template <typename _Ty>
void Printer(const Vector<_Ty>& vec) {
	std::for_each(
		vec.cbegin(), 
		vec.cend(), 
		[](const _Ty& x) -> void { 
			std::cout << x << std::endl; 
		}
	);
}

int main() {

	Vector<std::string> arr{ "asdf", "1234" };
	arr.PushBack("1");
	arr.PushBack("2");
	arr.PushBack("3");
	arr.PushBack("4");
	arr.PushBack("5");
	arr.PopBack();
	arr.PushBack("6");
	arr.PushBack("7");
	arr.PopBack();
	arr.PushBack("8");
	arr.PushBack("9");
	arr.PushBack("10");
	arr.PopBack();
	std::for_each(
		std::begin(arr),
		std::end(arr),
		[](std::string& x) -> void {
			std::cout << x << std::endl;
		}
	);

	Vector<Vector2i> vec{ { 1, 1 }, { 2, 2 }, { 3, 3 } };
	Vector2i x{ 4, 4 };
	vec.PushBack(x);
	vec.PushBack({ 5, 5 });
	vec.EmplaceBack(6, 6);
	vec.Insert(vec.begin(), { 7, 7 });
	vec.Erase(vec.end());
	Printer(vec);

	return 0;
}