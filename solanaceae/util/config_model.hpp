#pragma once

#include "./config_model.inl"

// TODO: events?
struct ConfigModelI {
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
};


