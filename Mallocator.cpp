#include "Mallocator.h"
#include <iostream>
#include <limits>

int main() {

	int* p = nonstd::allocator<int>().allocate(20);
	nonstd::allocator<int>().construct(p, 1);
	std::cout << *p << std::endl;
	return 0;
}