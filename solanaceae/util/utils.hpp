#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "./span.hpp"

[[nodiscard]] std::vector<uint8_t> hex2bin(const std::string& str);
[[nodiscard]] std::vector<uint8_t> hex2bin(const std::string_view str);
[[nodiscard]] std::string bin2hex(const ByteSpan bin);
[[nodiscard]] std::string bin2hex(const std::vector<uint8_t>& bin);

