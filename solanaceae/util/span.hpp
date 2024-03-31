#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <array>

// non owning view
template<typename T>
struct Span final {
	const T* ptr {nullptr};
	uint64_t size {0};

	constexpr Span(const Span&) = default;
	constexpr Span(Span&&) = default;
	constexpr Span(void) {}
	constexpr Span(const T* ptr_, uint64_t size_) : ptr(ptr_), size(size_) {}
	constexpr Span(T* ptr_, uint64_t size_) : ptr(ptr_), size(size_) {}
	constexpr explicit Span(const std::vector<T>& vec) : ptr(vec.data()), size(vec.size()) {}
	constexpr explicit Span(std::vector<T>& vec) : ptr(vec.data()), size(vec.size()) {}
	template<size_t N> constexpr explicit Span(const std::array<T, N>& arr) : ptr(arr.data()), size(arr.size()) {}
	template<size_t N> constexpr explicit Span(std::array<T, N>& arr) : ptr(arr.data()), size(arr.size()) {}

	Span& operator=(const Span& other) {
		ptr = other.ptr;
		size = other.size;
		return *this;
	}

	explicit operator std::vector<T>() const {
		return std::vector<T>{ptr, ptr+size};
	}

	constexpr const T& operator[](uint64_t i) const {
		if (i > size) {
			throw std::out_of_range("accessed span out of range");
		}

		return ptr[i];
	}

#if 0
	constexpr T& operator[](uint64_t i) {
		if (i > size) {
			throw std::out_of_range("accessed span out of range");
		}

		return ptr[i];
	}
#endif

	constexpr const T* cbegin(void) const { return ptr; }
	constexpr const T* cend(void) const { return ptr+size; }
	constexpr const T* begin(void) const { return ptr; }
	constexpr const T* end(void) const { return ptr+size; }

	constexpr bool empty(void) const { return ptr == nullptr || size == 0; }
};

// useful alias
using ByteSpan = Span<uint8_t>;
using ConstByteSpan = Span<const uint8_t>; // TODO: make use of?

