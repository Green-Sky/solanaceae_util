#pragma once

#include "./file2.hpp"

// write to vector or read from span
// no seeking for now (could make sense for read)

struct File2MemW : public File2I {
	std::vector<uint8_t>& _mem;

	File2MemW(std::vector<uint8_t>& mem);
	virtual ~File2MemW(void);

	bool isGood(void) override;

	bool write(const ByteSpan data, int64_t pos = -1) override;
	ByteSpanWithOwnership read(uint64_t size, int64_t pos = -1) override;
};

struct File2MemR : public File2I {
	ByteSpan _mem;
	int64_t _read_pos{0};

	File2MemR(ByteSpan mem);
	virtual ~File2MemR(void);

	bool isGood(void) override;

	bool write(const ByteSpan data, int64_t pos = -1) override;
	ByteSpanWithOwnership read(uint64_t size, int64_t pos = -1) override;
};

