#pragma once

#include "./config_model.inl"

#include <memory> // Q.Q

// TODO: events?
struct ConfigModelI {
	static constexpr const char* version {"2"};

	~ConfigModelI(void) {}

	// interface
	// level3
	// falls back to level2 value, if set
	virtual void set(CM_ISV module, CM_ISV category, CM_ISV entry, const bool value) = 0;
	virtual void set(CM_ISV module, CM_ISV category, CM_ISV entry, const int64_t value) = 0;
	virtual void set(CM_ISV module, CM_ISV category, CM_ISV entry, const double value) = 0;
	virtual void set(CM_ISV module, CM_ISV category, CM_ISV entry, CM_ISV value) = 0;
	virtual bool has_bool(CM_ISV module, CM_ISV category, CM_ISV entry) = 0;
	virtual bool has_int(CM_ISV module, CM_ISV category, CM_ISV entry) = 0;
	virtual bool has_double(CM_ISV module, CM_ISV category, CM_ISV entry) = 0;
	virtual bool has_string(CM_ISV module, CM_ISV category, CM_ISV entry) = 0;
	virtual CM_InternalOptional<bool> get_bool(CM_ISV module, CM_ISV category, CM_ISV entry) = 0;
	virtual CM_InternalOptional<int64_t> get_int(CM_ISV module, CM_ISV category, CM_ISV entry) = 0;
	virtual CM_InternalOptional<double> get_double(CM_ISV module, CM_ISV category, CM_ISV entry) = 0;
	virtual CM_InternalOptional<CM_ISV> get_string(CM_ISV module, CM_ISV category, CM_ISV entry) = 0;

	// level2
	virtual void set(CM_ISV module, CM_ISV category, const bool value) = 0;
	virtual void set(CM_ISV module, CM_ISV category, const int64_t value) = 0;
	virtual void set(CM_ISV module, CM_ISV category, const double value) = 0;
	virtual void set(CM_ISV module, CM_ISV category, CM_ISV value) = 0;
	virtual bool has_bool(CM_ISV module, CM_ISV category) = 0;
	virtual bool has_int(CM_ISV module, CM_ISV category) = 0;
	virtual bool has_double(CM_ISV module, CM_ISV category) = 0;
	virtual bool has_string(CM_ISV module, CM_ISV category) = 0;
	virtual CM_InternalOptional<bool> get_bool(CM_ISV module, CM_ISV category) = 0;
	virtual CM_InternalOptional<int64_t> get_int(CM_ISV module, CM_ISV category) = 0;
	virtual CM_InternalOptional<double> get_double(CM_ISV module, CM_ISV category) = 0;
	virtual CM_InternalOptional<CM_ISV> get_string(CM_ISV module, CM_ISV category) = 0;

	// iteration
	// actual range cant be virtual
	template<typename Type>
	struct ConstEntryProxy {
		struct Pair {
			std::string key;
			Type value;
		};

		struct ConstEntryIteratorI {
			virtual ~ConstEntryIteratorI(void) {}
			virtual std::unique_ptr<ConstEntryIteratorI> clone(void) = 0;
			virtual bool equal(const ConstEntryIteratorI& other) const = 0;
			virtual void incrementOne(void) = 0;
			//virtual const Type& getValue(void) const = 0;
			virtual Pair getValue(void) const = 0;
		};

		// actual iterator cant be virtual
		struct ConstEntryIterator {
			std::unique_ptr<ConstEntryIteratorI> _value;

			// conversion
			//ConstEntryIterator(const std::unique_ptr<ConstEntryIteratorI>& other) { _value = other._value->clone(); }
			ConstEntryIterator(std::unique_ptr<ConstEntryIteratorI>&& value) { _value = std::move(value); }

			// copy
			ConstEntryIterator(const ConstEntryIterator& other) { _value = other._value->clone(); }
			ConstEntryIterator& operator=(const ConstEntryIterator& other) { _value = other._value->clone(); return *this; }

			// move
			ConstEntryIterator(ConstEntryIterator&& other) { _value = std::move(other._value); }

			bool operator==(const ConstEntryIterator& other) const { return _value->equal(*other._value); }
			bool operator!=(const ConstEntryIterator& other) const { return !operator==(other); }
			ConstEntryIterator& operator++(void) { _value->incrementOne(); return *this; }
			Pair operator*(void) const { return _value->getValue(); }
		};

		ConstEntryIterator _begin;
		ConstEntryIterator _end;

		const ConstEntryIterator& begin(void) const { return _begin; }
		const ConstEntryIterator& end(void) const { return _end; }
	};

	// level 3
	virtual ConstEntryProxy<bool> entries_bool(CM_ISV module, CM_ISV category) const = 0;
	virtual ConstEntryProxy<int64_t> entries_int(CM_ISV module, CM_ISV category) const = 0;
	virtual ConstEntryProxy<double> entries_double(CM_ISV module, CM_ISV category) const = 0;
	virtual ConstEntryProxy<CM_ISV> entries_string(CM_ISV module, CM_ISV category) const = 0;
};


