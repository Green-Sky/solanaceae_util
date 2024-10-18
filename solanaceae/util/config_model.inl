#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <optional>
#include <type_traits>
#include <cassert>

// TODO: use pack(16) instead to guarantie same size on 32bit and 64bit?
#pragma pack(1)
struct CM_InternalStringView final {
	const char* start {nullptr};
	uint64_t extend {0};

	// conversion helpers
	CM_InternalStringView(const std::string_view sv) : start(sv.data()), extend(sv.size()) {}
	template<std::size_t N>
	CM_InternalStringView(const char (&str)[N]) : start(str), extend(N-1u) {}
	CM_InternalStringView(const std::string& str) : start(str.data()), extend(str.size()) {}
	operator std::string() { return {start, start+extend}; }
	operator std::string_view() { return {start, extend}; }
};
static_assert(sizeof(CM_InternalStringView) == sizeof(const char*) + sizeof(uint64_t), "guarantee abi (hope)");

using CM_ISV = CM_InternalStringView;
#pragma pack() // undo pack(1)

template<typename T>
struct CM_InternalOptional {
	bool has_value {false};
	union {
		bool b;
		int64_t i;
		double d;
		CM_InternalStringView s;
	};

	void set(bool v) { has_value = true; b = v; }
	void set(int64_t v) { has_value = true; i = v; }
	void set(double v) { has_value = true; d = v; }
	void set(CM_InternalStringView v) { has_value = true; s = v; }

	CM_InternalOptional(T v) : CM_InternalOptional(std::optional<T>{v}) {} // HACK: route through conv

	// conversion helpers
	CM_InternalOptional(std::nullopt_t) : has_value(false) {}

	CM_InternalOptional(std::optional<bool> opt) : has_value(opt.has_value()) { if (opt.has_value()) set(opt.value()); }
	CM_InternalOptional(std::optional<int64_t> opt) : has_value(opt.has_value()) { if (opt.has_value()) set(opt.value()); }
	CM_InternalOptional(std::optional<double> opt) : has_value(opt.has_value()) { if (opt.has_value()) set(opt.value()); }
	CM_InternalOptional(std::optional<CM_InternalStringView> opt) : has_value(opt.has_value()) { if (opt.has_value()) set(opt.value()); }

	//operator std::optional<T>(void) const = delete;

	operator auto() const {
		if (has_value) {
			if constexpr (std::is_same_v<T, bool>) {
				return std::optional{b};
			} else if constexpr (std::is_same_v<T, int64_t>) {
				return std::optional{i};
			} else if constexpr (std::is_same_v<T, double>) {
				return std::optional{d};
			} else if constexpr (std::is_same_v<T, CM_InternalStringView>) {
				return std::optional{s};
			}
		}
		return std::optional<T>{};
	}

	T value(void) {
		assert(has_value); // use exceptions instead?
		if constexpr (std::is_same_v<T, bool>) {
			return b;
		} else if constexpr (std::is_same_v<T, int64_t>) {
			return i;
		} else if constexpr (std::is_same_v<T, double>) {
			return d;
		} else if constexpr (std::is_same_v<T, CM_InternalStringView>) {
			return s;
		}
	}

	T& value_or(T& other) {
		if (has_value) {
			if constexpr (std::is_same_v<T, bool>) {
				return b;
			} else if constexpr (std::is_same_v<T, int64_t>) {
				return i;
			} else if constexpr (std::is_same_v<T, double>) {
				return d;
			} else if constexpr (std::is_same_v<T, CM_InternalStringView>) {
				return s;
			}
		} else {
			return other;
		}
	}

	const T& value_or(const T& other) const {
		if (has_value) {
			if constexpr (std::is_same_v<T, bool>) {
				return b;
			} else if constexpr (std::is_same_v<T, int64_t>) {
				return i;
			} else if constexpr (std::is_same_v<T, double>) {
				return d;
			} else if constexpr (std::is_same_v<T, CM_InternalStringView>) {
				return s;
			}
		} else {
			return other;
		}
	}

	T value_or(T&& other) {
		if (has_value) {
			if constexpr (std::is_same_v<T, bool>) {
				return b;
			} else if constexpr (std::is_same_v<T, int64_t>) {
				return i;
			} else if constexpr (std::is_same_v<T, double>) {
				return d;
			} else if constexpr (std::is_same_v<T, CM_InternalStringView>) {
				return s;
			}
		} else {
			return other;
		}
	}
};

