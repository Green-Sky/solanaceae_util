#include "./simple_config_model.hpp"

#include <iostream>

void SimpleConfigModel::set(CM_ISV module, CM_ISV category, CM_ISV entry, const bool value) { _map_bool[module][category].second[entry] = value; }

void SimpleConfigModel::set(CM_ISV module, CM_ISV category, CM_ISV entry, const int64_t value) { _map_int[module][category].second[entry] = value; }

void SimpleConfigModel::set(CM_ISV module, CM_ISV category, CM_ISV entry, const double value) { _map_double[module][category].second[entry] = value; }

void SimpleConfigModel::set(CM_ISV module, CM_ISV category, CM_ISV entry, CM_ISV value) { _map_string[module][category].second[entry] = value; }

bool SimpleConfigModel::has_bool(CM_ISV module, CM_ISV category, CM_ISV entry) { return _map_bool.count(module) && _map_bool[module].count(category) && _map_bool[module][category].second.count(entry); }

bool SimpleConfigModel::has_int(CM_ISV module, CM_ISV category, CM_ISV entry) { return _map_int.count(module) && _map_int[module].count(category) && _map_int[module][category].second.count(entry); }

bool SimpleConfigModel::has_double(CM_ISV module, CM_ISV category, CM_ISV entry) { return _map_double.count(module) && _map_double[module].count(category) && _map_double[module][category].second.count(entry); }

bool SimpleConfigModel::has_string(CM_ISV module, CM_ISV category, CM_ISV entry) { return _map_string.count(module) && _map_string[module].count(category) && _map_string[module][category].second.count(entry); }

CM_InternalOptional<bool> SimpleConfigModel::get_bool(CM_ISV module, CM_ISV category, CM_ISV entry) {
	auto& map = _map_bool;
	if (!map.count(module) || !map[module].count(category)) {
		return std::nullopt;
	} else if (map[module][category].second.count(entry)) {
		return map[module][category].second[entry];
	} else {
		return map[module][category].first;
	}
}

CM_InternalOptional<int64_t> SimpleConfigModel::get_int(CM_ISV module, CM_ISV category, CM_ISV entry) {
	auto& map = _map_int;
	if (!map.count(module) || !map[module].count(category)) {
		return std::nullopt;
	} else if (map[module][category].second.count(entry)) {
		return map[module][category].second[entry];
	} else {
		return map[module][category].first;
	}
}

CM_InternalOptional<double> SimpleConfigModel::get_double(CM_ISV module, CM_ISV category, CM_ISV entry) {
	auto& map = _map_double;
	if (!map.count(module) || !map[module].count(category)) {
		return std::nullopt;
	} else if (map[module][category].second.count(entry)) {
		return map[module][category].second[entry];
	} else {
		return map[module][category].first;
	}
}

CM_InternalOptional<CM_ISV> SimpleConfigModel::get_string(CM_ISV module, CM_ISV category, CM_ISV entry) {
	auto& map = _map_string;
	if (!map.count(module) || !map[module].count(category)) {
		return std::nullopt;
	} else if (map[module][category].second.count(entry)) {
		return CM_ISV{map[module][category].second[entry]};
	} else if (map[module][category].first.has_value()){
		return CM_ISV{map[module][category].first.value()};
	} else {
		return std::nullopt;
	}
}

void SimpleConfigModel::set(CM_ISV module, CM_ISV category, const bool value) { _map_bool[module][category].first = value; }

void SimpleConfigModel::set(CM_ISV module, CM_ISV category, const int64_t value) { _map_int[module][category].first = value; }

void SimpleConfigModel::set(CM_ISV module, CM_ISV category, const double value) { _map_double[module][category].first = value; }

void SimpleConfigModel::set(CM_ISV module, CM_ISV category, CM_ISV value) { _map_string[module][category].first = value; }

bool SimpleConfigModel::has_bool(CM_ISV module, CM_ISV category) { return _map_bool.count(module) && _map_bool[module].count(category) && _map_bool[module][category].first.has_value(); }

bool SimpleConfigModel::has_int(CM_ISV module, CM_ISV category) { return _map_int.count(module) && _map_int[module].count(category) && _map_int[module][category].first.has_value(); }

bool SimpleConfigModel::has_double(CM_ISV module, CM_ISV category) { return _map_double.count(module) && _map_double[module].count(category) && _map_double[module][category].first.has_value(); }

bool SimpleConfigModel::has_string(CM_ISV module, CM_ISV category) { return _map_string.count(module) && _map_string[module].count(category) && _map_string[module][category].first.has_value(); }

CM_InternalOptional<bool> SimpleConfigModel::get_bool(CM_ISV module, CM_ISV category) {
	auto& map = _map_bool;
	if (!map.count(module) || !map[module].count(category)) {
		return std::nullopt;
	} else {
		return map[module][category].first;
	}
}

CM_InternalOptional<int64_t> SimpleConfigModel::get_int(CM_ISV module, CM_ISV category) {
	auto& map = _map_int;
	if (!map.count(module) || !map[module].count(category)) {
		return std::nullopt;
	} else {
		return map[module][category].first;
	}
}

CM_InternalOptional<double> SimpleConfigModel::get_double(CM_ISV module, CM_ISV category) {
	auto& map = _map_double;
	if (!map.count(module) || !map[module].count(category)) {
		return std::nullopt;
	} else {
		return map[module][category].first;
	}
}

CM_InternalOptional<CM_ISV> SimpleConfigModel::get_string(CM_ISV module, CM_ISV category) {
	auto& map = _map_string;
	if (!map.count(module) || !map[module].count(category)) {
		return std::nullopt;
	} else if (map[module][category].first.has_value()){
		return CM_ISV{map[module][category].first.value()};
	} else {
		return std::nullopt;
	}
}

// iteration

// level 3
ConfigModelI::ConstEntryProxy<bool> SimpleConfigModel::entries_bool(CM_ISV module, CM_ISV category) const {
	using Type = bool;
	using RealType = Type;
	static std::map<std::string, RealType> g_empty_map;
	auto& map = _map_bool;
	if (map.count(module) && map.at(module).count(category)) {
		const auto& tmp_map = map.at(module).at(category).second;
		return SimpleConstEntryIteratorImpl<Type, RealType>::createRange(
			tmp_map.cbegin(),
			tmp_map.cend()
		);
	}
	return SimpleConstEntryIteratorImpl<Type, RealType>::createRange(g_empty_map.cbegin(), g_empty_map.cend());
}

ConfigModelI::ConstEntryProxy<int64_t> SimpleConfigModel::entries_int(CM_ISV module, CM_ISV category) const {
	using Type = int64_t;
	using RealType = Type;
	static std::map<std::string, RealType> g_empty_map;
	auto& map = _map_int;
	if (map.count(module) && map.at(module).count(category)) {
		const auto& tmp_map = map.at(module).at(category).second;
		return SimpleConstEntryIteratorImpl<Type, RealType>::createRange(
			tmp_map.cbegin(),
			tmp_map.cend()
		);
	}
	return SimpleConstEntryIteratorImpl<Type, RealType>::createRange(g_empty_map.cbegin(), g_empty_map.cend());
}

ConfigModelI::ConstEntryProxy<double> SimpleConfigModel::entries_double(CM_ISV module, CM_ISV category) const {
	using Type = double;
	using RealType = Type;
	static std::map<std::string, RealType> g_empty_map;
	auto& map = _map_double;
	if (map.count(module) && map.at(module).count(category)) {
		const auto& tmp_map = map.at(module).at(category).second;
		return SimpleConstEntryIteratorImpl<Type, RealType>::createRange(
			tmp_map.cbegin(),
			tmp_map.cend()
		);
	}
	return SimpleConstEntryIteratorImpl<Type, RealType>::createRange(g_empty_map.cbegin(), g_empty_map.cend());
}

ConfigModelI::ConstEntryProxy<CM_ISV> SimpleConfigModel::entries_string(CM_ISV module, CM_ISV category) const {
	using Type = CM_ISV;
	using RealType = std::string;
	static std::map<std::string, RealType> g_empty_map;
	auto& map = _map_string;
	if (map.count(module) && map.at(module).count(category)) {
		const auto& tmp_map = map.at(module).at(category).second;
		return SimpleConstEntryIteratorImpl<Type, RealType>::createRange(
			tmp_map.cbegin(),
			tmp_map.cend()
		);
	}
	return SimpleConstEntryIteratorImpl<Type, RealType>::createRange(g_empty_map.cbegin(), g_empty_map.cend());
}

void SimpleConfigModel::dump(void) {
	std::cout << "SCM dump:\n";
	for (const auto& [k_m, v_c] : _map_bool) {
		for (const auto& [k_c, v_e] : v_c) {
			if (v_e.first.has_value()) {
				std::cout << "  " << k_m << "::" << k_c << " = " << (v_e.first.value()?"true":"false") << "\n";
			}

			for (const auto& [k_e, e] : v_e.second) {
				std::cout << "  " << k_m << "::" << k_c << "::" << k_e << " = " << (e?"true":"false") << "\n";
			}
		}
	}
	for (const auto& [k_m, v_c] : _map_int) {
		for (const auto& [k_c, v_e] : v_c) {
			if (v_e.first.has_value()) {
				std::cout << "  " << k_m << "::" << k_c << " = " << v_e.first.value() << "\n";
			}

			for (const auto& [k_e, e] : v_e.second) {
				std::cout << "  " << k_m << "::" << k_c << "::" << k_e << " = " << e << "\n";
			}
		}
	}
	for (const auto& [k_m, v_c] : _map_double) {
		for (const auto& [k_c, v_e] : v_c) {
			if (v_e.first.has_value()) {
				std::cout << "  " << k_m << "::" << k_c << " = " << v_e.first.value() << "\n";
			}

			for (const auto& [k_e, e] : v_e.second) {
				std::cout << "  " << k_m << "::" << k_c << "::" << k_e << " = " << e << "\n";
			}
		}
	}
	for (const auto& [k_m, v_c] : _map_string) {
		for (const auto& [k_c, v_e] : v_c) {
			if (v_e.first.has_value()) {
				std::cout << "  " << k_m << "::" << k_c << " = " << v_e.first.value() << "\n";
			}

			for (const auto& [k_e, e] : v_e.second) {
				std::cout << "  " << k_m << "::" << k_c << "::" << k_e << " = " << e << "\n";
			}
		}
	}
}

