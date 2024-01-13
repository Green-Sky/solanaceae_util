#pragma once

#include <string>
#include <string_view>
#include <vector>

[[nodiscard]] std::vector<uint8_t> hex2bin(const std::string& str);
[[nodiscard]] std::vector<uint8_t> hex2bin(const std::string_view str);
[[nodiscard]] std::string bin2hex(const std::vector<uint8_t>& bin);

