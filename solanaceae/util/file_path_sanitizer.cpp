#include "./file_path_sanitizer.hpp"

std::string sanitize_file_name(std::string_view file_name) {
	std::string sanitized_name{file_name};
	if (file_name.empty()) {
		return sanitized_name;
	}

	// basically all ntfs rules
	// https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file

	for (const char it : {'\0', '<', '>', ':', '"', '/', '\\', '|', '?', '*'}) {
		for (char& ch : sanitized_name) {
			if (ch == it) {
				ch = '_';
			}
		}
	}

	if (sanitized_name.back() == '.' || sanitized_name.back() == ' ') {
		sanitized_name.back() = '_';
	}

	// TODO: problematic file names like COM etc

	return sanitized_name;
}

// TODO: impl
//std::filesystem::path sanitize_path(const std::filesystem::path& path) {
//    // split path into nodes and sanitize each node by name, then reconstruct as path
//}
