#pragma once
#include <stdlib.h>
#include <new>
#include <limits>
#include <memory>
#include <iostream>


namespace nonstd {




	template<typename T>
	void resolver(T* pointer, T v) {
		if (pointer != nullptr)
			*pointer = v;
		else throw std::runtime_error("passed nullptr");
	}

	template<typename T, typename ... Args>
	void resolver(T* pointer, T first, Args&&... args) {
		resolver(pointer, first);
		pointer++;
		resolver(pointer, args...);
	}
	template<typename T>
	class allocator {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef const T* const_pointer;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		template<class U> struct rebind {
			typedef allocator<U> other;
		};

		allocator() noexcept {

		}

		allocator(const allocator<T>& alloc) noexcept {

		}
		template<class U>
		allocator(const allocator<U>& alloc) noexcept {

		}
		~allocator() = default;
		template<class U>
		bool operator==(const allocator<U>&) const noexcept {
			return true;
		}
		template<class U>
		bool operator!=(const allocator<U>&) const noexcept {
			return false;
		}
		pointer allocate(const size_type n) const
		{
			if (n < 0) {
				throw std::bad_alloc();
			}
			if (n == 0) {
				return nullptr;
			}
			if (n > static_cast<size_t>(-1) / sizeof(T)) {
				throw std::bad_array_new_length();
			}
			void* const pv = malloc(n * sizeof(T));
			if (!pv) {
				throw std::bad_alloc();
			}
			return static_cast<T*>(pv);
		}
		void deallocate(pointer p, size_t n=1)const noexcept {
			for (pointer i = p; i != (p + n); ++i) {
				if (i != nullptr)
					free(i);
			}
		}
		void destroy(pointer p) {
			((T*)p)->~T();
		}

		template<class U>
		void destroy(U* p) noexcept {
			p->~U();
		}
		template<class... Args>
		void construct(T* p, Args&&... args) {
			resolver(p, args...);
		}
		size_type max_size() const noexcept {
			// need to finish
			//	return std::numeric_limits<T>::max();
		}

		pointer address(reference x) const {
			return &x;
		}
		const_pointer address(const_reference x)const {
			return &x;
		}
	private:

	};
	template<class _Alloc>
	struct allocator_traits {
		typedef _Alloc allocator_type;
		// finish
	};
};