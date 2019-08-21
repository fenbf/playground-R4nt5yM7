#include <cassert>
#include <cstdint>
#include <iostream>
#include <malloc.h>
#include <new>

/*void* operator new(std::size_t size) {
	auto ptr = malloc(size);
	if (!ptr)
		throw std::bad_alloc{};
	std::cout << "new: " << size << ", ptr: " << ptr << '\n';
	return ptr;
}

void operator delete(void* ptr, std::size_t size) {
	std::cout << "delete: " << size << ", ptr: " << ptr << '\n';
	free(ptr);
}

void operator delete(void* ptr) {
	std::cout << "delete: ptr: " << ptr << '\n';
	free(ptr);
}*/

void* operator new(std::size_t size, std::align_val_t align) {
#ifdef _MSC_VER
	auto ptr = _aligned_malloc(size, static_cast<std::size_t>(align));
#else
	auto ptr = aligned_alloc(static_cast<std::size_t>(align), size);
#endif

	if (!ptr)
		throw std::bad_alloc{};

	std::cout << "new: " << size << ", align: " << static_cast<std::size_t>(align) << ", ptr: " << ptr << '\n';
	
	return ptr;
}

void operator delete(void* ptr, std::size_t size, std::align_val_t align) {
	std::cout << "delete: " << size << ", align: " << static_cast<std::size_t>(align) << ", ptr : " << ptr << '\n';
#ifdef _MSC_VER	
	_aligned_free(ptr);
#else
	free(ptr);
#endif
}

void operator delete(void* ptr, std::align_val_t align) {
	std::cout << "delete: align: " << static_cast<std::size_t>(align) << ", ptr : " << ptr << '\n';
#ifdef _MSC_VER	
	_aligned_free(ptr);
#else
	free(ptr);
#endif
}

class alignas(32) Vec3dAVX { 
	double x, y, z;
};

int main() {
	std::cout << "__STDCPP_DEFAULT_NEW_ALIGNMENT__ is " << __STDCPP_DEFAULT_NEW_ALIGNMENT__ << std::endl;

	std::cout << "sizeof(Vec3dAVX) is " << sizeof(Vec3dAVX) << '\n';
	std::cout << "alignof(Vec3dAVX) is " << alignof(Vec3dAVX) << '\n';
	auto pVec = new Vec3dAVX[10];
	assert(reinterpret_cast<uintptr_t>(pVec) % alignof(Vec3dAVX) == 0);
	delete[] pVec;

	auto p2 = new int[10];
	delete[] p2;
}