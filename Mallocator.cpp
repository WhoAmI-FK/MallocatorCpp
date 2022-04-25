#include "Mallocator.h"
#include <iostream>
#include <limits>


int main() {
	try {
		int* p = nonstd::allocator<int>().allocate(20);
		nonstd::allocator<int>().construct(p, 1, 2, 3, 4);
		std::cout << *p << std::endl;
		std::cout << *(p + 1) << std::endl;
		std::cout << *(p + 2) << std::endl;
		std::cout << *(p + 3) << std::endl;
		nonstd::allocator<int>().destroy(p + 3);
		std::cout << *(p + 3);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}