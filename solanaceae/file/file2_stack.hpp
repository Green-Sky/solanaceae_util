#pragma once

#include "./file2.hpp"

#include <stack>
#include <memory>

// wrapper/container for a file "stack"
// has no file functionallity by itself

struct File2Stack : public File2I {
	std::stack<std::unique_ptr<File2I>> _stack;

	// TODO: change interface again and make r/w non const data members!
	File2Stack(void) : File2I(false, false), _stack() {}
	File2Stack(std::stack<std::unique_ptr<File2I>>&& stack) : File2I(false, false), _stack(std::move(stack)) {}
	File2Stack(std::unique_ptr<File2I>&& file) : File2I(false, false), _stack({std::move(file)}) {}
	virtual ~File2Stack(void) {}

	bool isGood(void) override {
		return _stack.top()->isGood();
	}

	bool write(const ByteSpan data, int64_t pos = -1) override {
		return _stack.top()->write(data, pos);
	}

	ByteSpanWithOwnership read(uint64_t size, int64_t pos = -1) override {
		return _stack.top()->read(size, pos);
	}
};

