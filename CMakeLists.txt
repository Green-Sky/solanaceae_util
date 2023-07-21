cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(solanaceae)

add_library(solanaceae_util
	./solanaceae/util/config_model.hpp
	./solanaceae/util/config_model.inl

	./solanaceae/util/simple_config_model.hpp
	./solanaceae/util/simple_config_model.cpp
)

target_include_directories(solanaceae_util PUBLIC .)
target_compile_features(solanaceae_util PUBLIC cxx_std_17)
#target_link_libraries(solanaceae_util PUBLIC
#)

