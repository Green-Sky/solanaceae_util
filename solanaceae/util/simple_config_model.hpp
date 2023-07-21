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

	// debug
	void dump(void);
};

