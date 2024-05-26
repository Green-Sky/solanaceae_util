#include "./file2_std.hpp"

#include <limits>
#include <vector>

// why is this so ugly?
// WARNING: has g pos side effect
static uint64_t get_file_size(std::fstream& f) {
	// figure out size
	f.seekg(0, f.end);
	uint64_t file_size = f.tellg();
	f.seekg(0, f.beg);
	return file_size;
}

File2WFile::File2WFile(std::string_view file_path, bool trunc) :
	File2I(true, false),
	_file(
		static_cast<std::string>(file_path),
		std::ios::out |
		(trunc ? std::ios::trunc | std::ios::binary : std::ios::binary) // hacky but type safe
	)
{
	_file_size = get_file_size(_file);

	if (!_file.is_open()) {
		return; // TODO: error
	}
}

bool File2WFile::isGood(void) {
	return _file.is_open() && _file.good();
}

bool File2WFile::write(const ByteSpan data, int64_t pos) {
	if (pos != -1) {
		//std::cerr << "invalid pos\n";
		return false;
	}

	if (data.empty()) {
		//std::cerr << "no data\n";
		return false; // true instead?
	}

	_file.write(reinterpret_cast<const char*>(data.ptr), data.size);

	return _file.good();
}

ByteSpanWithOwnership File2WFile::read(uint64_t, int64_t) {
	return ByteSpan{};
}

File2RWFile::File2RWFile(std::string_view file_path, uint64_t file_size, bool trunc) :
	File2I(true, true),
	_file(
		static_cast<std::string>(file_path),
		std::ios::in |
		std::ios::out |
		(trunc ? std::ios::trunc | std::ios::binary : std::ios::binary) // hacky but type safe
	)
{
	if (file_size == -1) {
		_file_size = get_file_size(_file);
	} else {
		_file_size = file_size;
	}

	if (!_file.is_open()) {
		return; // TODO: error
	}
}

bool File2RWFile::isGood(void) {
	return _file.is_open() && _file.good();
}

bool File2RWFile::write(const ByteSpan data, int64_t pos) {
	if (pos >= _file_size) {
		return false;
	}

	if (data.empty()) {
		return false; // true instead?
	}

	// if out-of-order, seek
	if (pos >= 0 && _file.tellp() != int64_t(pos)) {
		// TODO: error check
		if (_file.seekp(pos, std::ios::beg).fail()) {
			return false;
		}
	} else if (pos < -1) {
		// error !!!!
		return false;
	}

	_file.write(reinterpret_cast<const char*>(data.ptr), data.size);

	return _file.good();
}

ByteSpanWithOwnership File2RWFile::read(uint64_t size, int64_t pos) {
	if (pos >= int64_t(_file_size)) {
		return ByteSpan{};
	}

	if (pos != -1) {
		// TODO: error check
		_file.seekg(pos, std::ios::beg);
	} else if (pos < -1) {
		// error !!!!
		return ByteSpan{};
	}

	// we copy the data from file (not mapped)
	std::vector<uint8_t> chunk(size);
	const auto nread = _file.read(reinterpret_cast<char*>(chunk.data()), chunk.size()).gcount();
	if (nread != std::numeric_limits<std::streamsize>::max()) {
		chunk.resize(nread); // usually a noop
	} else {
		chunk.clear();
	}

	// return owning
	return ByteSpanWithOwnership{std::move(chunk)};
	//return chunk; // is this the same?
}

