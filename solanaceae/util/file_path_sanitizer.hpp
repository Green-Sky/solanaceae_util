#pragma once

#include <string>
#include <string_view>
//#include <filesystem>

// only pass utf8 names, so without /. it will replace / if passed
std::string sanitize_file_name(std::string_view file_name);
// TODO: folder name too?

// TODO: impl
//std::filesystem::path sanitize_path(const std::filesystem::path& path);
