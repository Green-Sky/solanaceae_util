#include "./file_synced.hpp"

#include <stdexcept>
#include <string>

#if defined(_WIN32) || defined(WIN32)

#include <iostream>

#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif

#	include <windows.h>
#	include <fileapi.h>

void write_to_file_synced(const std::filesystem::path& file_path, const uint8_t* data, size_t data_size) {
	// cant use FILE_FLAG_NO_BUFFERING, FILE_FLAG_WRITE_THROUGH has to be enough
	const auto fd = CreateFileW(
		file_path.native().c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH,
		nullptr
	);

	if (fd == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("file creation error: " + std::to_string(GetLastError()));
	}

	DWORD bytes_written {0};
	if (!WriteFile(fd, data, data_size, &bytes_written, nullptr)) {
		CloseHandle(fd);
		throw std::runtime_error("write error: " + std::to_string(GetLastError()));
	} else if (bytes_written != data_size) {
		CloseHandle(fd);
		throw std::runtime_error("write error, only written " + std::to_string(bytes_written) + " instead of " + std::to_string(data_size));
	}

	CloseHandle(fd);
}

#else

#	include <fcntl.h>
#	include <unistd.h>
#	include <cerrno>
#	include <cstring>

void write_to_file_synced(const std::filesystem::path& file_path, const uint8_t* data, size_t data_size) {
	// cant use O_DIRECT, O_SYNC has to be enough
	const auto fd = open(file_path.generic_u8string().c_str(), O_CREAT | O_WRONLY | O_TRUNC | O_SYNC, S_IRUSR | S_IWUSR /*| S_IRGRP*/);
	if (fd == -1) {
		throw std::runtime_error("file creation error: " + std::string(strerror(errno)));
	}
	const auto wret = write(fd, data, data_size);
	if (wret == -1) {
		close(fd);
		throw std::runtime_error("write error: " + std::string(strerror(errno)));
	} else if (size_t(wret) != data_size) {
		close(fd);
		throw std::runtime_error("write error: file not fully written");
	}
	close(fd);
}

#endif
