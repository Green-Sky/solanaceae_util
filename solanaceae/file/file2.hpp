#pragma once

#include <solanaceae/util/span.hpp>

#include <vector>
#include <variant>

// TODO: move to/next-to span
// a span that can also represent its ownership
template<typename T>
struct SpanWithOwnership : public Span<T> {
	// TODO: allow for different owners
	std::vector<T> _data_owner;

	// self interactions
	SpanWithOwnership(void) = delete;
	constexpr SpanWithOwnership(const SpanWithOwnership&) = delete;
	constexpr SpanWithOwnership(SpanWithOwnership&&) = default;

	// non-owning
	constexpr SpanWithOwnership(const Span<T>& span) : Span<T>(span) {}
	constexpr SpanWithOwnership(const Span<T>&& span) : Span<T>(span) {}

	// owning
	constexpr SpanWithOwnership(std::vector<T>&& data) : Span<T>(data), _data_owner(std::move(data)) {}

	bool isOwning(void) const { return !_data_owner.empty(); }
};
using ByteSpanWithOwnership = SpanWithOwnership<uint8_t>;

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
	//[[nodiscard]] virtual std::variant<ByteSpan, std::vector<uint8_t>> read(uint64_t size, int64_t pos = -1) = 0;
	[[nodiscard]] virtual ByteSpanWithOwnership read(uint64_t size, int64_t pos = -1) = 0;
};

