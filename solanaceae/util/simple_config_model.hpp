#pragma once

#include "./config_model.hpp"

#include <map>

struct SimpleConfigModel : public ConfigModelI {
	std::map<std::string, std::map<std::string, std::pair<std::optional<bool>, std::map<std::string, bool>>>> _map_bool;
	std::map<std::string, std::map<std::string, std::pair<std::optional<int64_t>, std::map<std::string, int64_t>>>> _map_int;
	std::map<std::string, std::map<std::string, std::pair<std::optional<double>, std::map<std::string, double>>>> _map_double;
	std::map<std::string, std::map<std::string, std::pair<std::optional<std::string>, std::map<std::string, std::string>>>> _map_string;

	// level3
	void set(CM_ISV module, CM_ISV category, CM_ISV entry, const bool value) override;
	void set(CM_ISV module, CM_ISV category, CM_ISV entry, const int64_t value) override;
	void set(CM_ISV module, CM_ISV category, CM_ISV entry, const double value) override;
	void set(CM_ISV module, CM_ISV category, CM_ISV entry, CM_ISV value) override;
	bool has_bool(CM_ISV module, CM_ISV category, CM_ISV entry) override;
	bool has_int(CM_ISV module, CM_ISV category, CM_ISV entry) override;
	bool has_double(CM_ISV module, CM_ISV category, CM_ISV entry) override;
	bool has_string(CM_ISV module, CM_ISV category, CM_ISV entry) override;

	CM_InternalOptional<bool> get_bool(CM_ISV module, CM_ISV category, CM_ISV entry) override;
	CM_InternalOptional<int64_t> get_int(CM_ISV module, CM_ISV category, CM_ISV entry) override;
	CM_InternalOptional<double> get_double(CM_ISV module, CM_ISV category, CM_ISV entry) override;
	CM_InternalOptional<CM_ISV> get_string(CM_ISV module, CM_ISV category, CM_ISV entry) override;

	// level2
	void set(CM_ISV module, CM_ISV category, const bool value) override;
	void set(CM_ISV module, CM_ISV category, const int64_t value) override;
	void set(CM_ISV module, CM_ISV category, const double value) override;
	void set(CM_ISV module, CM_ISV category, CM_ISV value) override;
	bool has_bool(CM_ISV module, CM_ISV category) override;
	bool has_int(CM_ISV module, CM_ISV category) override;
	bool has_double(CM_ISV module, CM_ISV category) override;
	bool has_string(CM_ISV module, CM_ISV category) override;
	CM_InternalOptional<bool> get_bool(CM_ISV module, CM_ISV category) override;
	CM_InternalOptional<int64_t> get_int(CM_ISV module, CM_ISV category) override;
	CM_InternalOptional<double> get_double(CM_ISV module, CM_ISV category) override;
	CM_InternalOptional<CM_ISV> get_string(CM_ISV module, CM_ISV category) override;

	// iteration
	template<typename Type, typename RealType = Type>
	struct SimpleConstEntryIteratorImpl : public ConfigModelI::ConstEntryProxy<Type>::ConstEntryIteratorI {
		using BaseType = typename ConfigModelI::ConstEntryProxy<Type>;
		using BaseIteratorIType = typename ConfigModelI::ConstEntryProxy<Type>::ConstEntryIteratorI;
		using MapType = std::map<std::string, RealType>;
		using MapTypeIterator = typename MapType::const_iterator;

		MapTypeIterator _self;

		SimpleConstEntryIteratorImpl(const MapTypeIterator& self) : _self(self) {}
		SimpleConstEntryIteratorImpl(void) {}

		virtual ~SimpleConstEntryIteratorImpl(void) {}
		std::unique_ptr<BaseIteratorIType> clone(void) override { return std::make_unique<SimpleConstEntryIteratorImpl>(_self); }
		bool equal(const BaseIteratorIType& other) const override { return _self == static_cast<const SimpleConstEntryIteratorImpl&>(other)._self; }
		void incrementOne(void) override { ++_self; }
		typename BaseType::Pair getValue(void) const override { return {_self->first, _self->second}; }

		// helper
		static ConfigModelI::ConstEntryProxy<Type> createRange(const MapTypeIterator& begin, const MapTypeIterator& end) {
			return {
				SimpleConstEntryIteratorImpl{begin}.clone(),
				SimpleConstEntryIteratorImpl{end}.clone()
			};
		}
	};

	// level 3
	ConfigModelI::ConstEntryProxy<bool> entries_bool(CM_ISV module, CM_ISV category) const override;
	ConfigModelI::ConstEntryProxy<int64_t> entries_int(CM_ISV module, CM_ISV category) const override;
	ConfigModelI::ConstEntryProxy<double> entries_double(CM_ISV module, CM_ISV category) const override;
	ConfigModelI::ConstEntryProxy<CM_ISV> entries_string(CM_ISV module, CM_ISV category) const override;

	// debug
	void dump(void);
};

