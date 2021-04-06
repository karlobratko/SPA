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
	/*Vector<char> vec{ 'k', 'a', 'r', 'l', 'o' };
	char x = ' ';
	vec.PushBack(x);
	vec.EmplaceBack('d');
	vec.Insert(vec.begin(), 'r');
	vec.Erase(vec.begin() + 1);
	Printer(vec);*/

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