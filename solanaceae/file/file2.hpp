#pragma once

#include <solanaceae/util/span.hpp>

#include <vector>
#include <variant>

struct File2I {
	// read only
	uint64_t _file_size {0};

	const bool can_write {false};
	const bool can_read {false};
	// TODO: non-seekable files?

	explicit File2I(bool can_write_, bool can_read_) : can_write(can_write_), can_read(can_read_) {}
	virtual ~File2I(void) {}

	virtual bool isGood(void) = 0;

	// pos -1 means stream, append to last written, or read position (independent, like FILE*s)
	virtual bool write(const ByteSpan data, int64_t pos = -1) = 0;
	[[nodiscard]] virtual std::variant<ByteSpan, std::vector<uint8_t>> read(uint64_t size, int64_t pos = -1) = 0;
};

