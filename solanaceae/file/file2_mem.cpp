#include "./file2_mem.hpp"

File2MemW::File2MemW(std::vector<uint8_t>& mem) : File2I(true, false), _mem(mem) {
}

File2MemW::~File2MemW(void) {
}

bool File2MemW::isGood(void) {
	// TODO: are there any error cases?
	return true;
}

bool File2MemW::write(const ByteSpan data, int64_t pos) {
	if (pos != -1) { // only support streaming
		return false;
	}

	if (data.empty()) {
		return false; // true instead?
	}

	_mem.insert(_mem.cend(), data.cbegin(), data.cend());

	return isGood();
}

ByteSpanWithOwnership File2MemW::read(uint64_t size, int64_t pos) {
	return ByteSpan{};
}

File2MemR::File2MemR(ByteSpan mem) : File2I(false, true), _mem(mem) {
}

File2MemR::~File2MemR(void) {
}

bool File2MemR::isGood(void) {
	// TODO: return false if eof?
	return true;
}

bool File2MemR::write(const ByteSpan data, int64_t pos) {
	return false;
}

ByteSpanWithOwnership File2MemR::read(uint64_t size, int64_t pos) {
	if (_read_pos >= _mem.size) {
		return ByteSpan{};
	}

	ByteSpan ret {
		_mem.ptr + _read_pos,
		std::min(size, _mem.size - _read_pos)
	};
	_read_pos += ret.size;
	// return non-owning
	return ret;
}

