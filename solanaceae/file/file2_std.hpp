#pragma once

#include "./file2.hpp"

#include <fstream>

// std fstream backed files

// write steam file
// no preallocation required, but seeking is disabled
struct File2WFile : public File2I {
	std::fstream _file;

	// dont truncate by default
	File2WFile(std::string_view file_path, bool trunc = false);

	virtual ~File2WFile(void) {}

	bool isGood(void) override;

	bool write(const ByteSpan data, int64_t pos = -1) override;
	ByteSpanWithOwnership read(uint64_t size, int64_t pos = -1) override;
};

// read write, requires an existing file, file size is fixed
struct File2RWFile : public File2I {
	std::fstream _file;

	// dont truncate by default
	// pass -1 for fetching the size from file
	File2RWFile(std::string_view file_path, uint64_t file_size = -1, bool trunc = false);

	virtual ~File2RWFile(void) {}

	bool isGood(void) override;

	bool write(const ByteSpan data, int64_t pos = -1) override;
	ByteSpanWithOwnership read(uint64_t size, int64_t pos = -1) override;
};

// cut down interface (write disabled)
// TODO: remove
struct File2RFile : public File2RWFile {
	File2RFile(std::string_view file_path) : File2RWFile(file_path) {}
	virtual ~File2RFile(void) {}
	using File2RWFile::isGood;
	using File2RWFile::read;
	bool write(const ByteSpan, int64_t = -1) override { return false; }
};

