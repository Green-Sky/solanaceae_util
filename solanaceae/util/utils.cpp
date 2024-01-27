#include "./utils.hpp"

#include <cassert>

namespace detail {
	constexpr uint8_t nib_from_hex(char c) {
		assert((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));

		if (c >= '0' && c <= '9') {
			return static_cast<uint8_t>(c) - '0';
		} else if (c >= 'a' && c <= 'f') {
			return (static_cast<uint8_t>(c) - 'a') + 10u;
		} else if (c >= 'A' && c <= 'F') {
			return (static_cast<uint8_t>(c) - 'A') + 10u;
		} else {
			return 0u;
		}
	}

	constexpr char nib_to_hex(uint8_t c) {
		assert(c <= 0x0f);

		if (c <= 0x09) {
			return c + '0';
		} else {
			return (c - 10u) + 'a';
		}
	}
} // detail

std::vector<uint8_t> hex2bin(const std::string& str) {
	return hex2bin(std::string_view{str});
}

std::vector<uint8_t> hex2bin(const std::string_view str) {
	assert(str.size() % 2 == 0); // TODO: should this be a hard assert??
	std::vector<uint8_t> bin{};
	bin.resize(str.size()/2, 0);

	for (size_t i = 0; i < bin.size(); i++) {
		bin[i] = detail::nib_from_hex(str[i*2]) << 4 | detail::nib_from_hex(str[i*2+1]);
	}

	return bin;
}

std::string bin2hex(const std::vector<uint8_t>& data) {
	std::string str;
	for (size_t i = 0; i < data.size(); i++) {
		str.push_back(detail::nib_to_hex(data[i] >> 4));
		str.push_back(detail::nib_to_hex(data[i] & 0x0f));
	}
	return str;
}

