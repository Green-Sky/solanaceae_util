cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(solanaceae)

add_library(solanaceae_util
	./solanaceae/util/span.hpp

	./solanaceae/util/utils.hpp
	./solanaceae/util/utils.cpp

	./solanaceae/util/uuid_generator.hpp
	./solanaceae/util/uuid_generator.cpp

	./solanaceae/util/config_model.hpp
	./solanaceae/util/config_model.inl

	./solanaceae/util/simple_config_model.hpp
	./solanaceae/util/simple_config_model.cpp

	./solanaceae/util/event_provider.hpp
)

target_include_directories(solanaceae_util PUBLIC .)
target_compile_features(solanaceae_util PUBLIC cxx_std_17)
#target_link_libraries(solanaceae_util PUBLIC
#)

########################################

add_library(solanaceae_file2
	./solanaceae/file/file2.hpp
	./solanaceae/file/file2_std.hpp
	./solanaceae/file/file2_std.cpp
	./solanaceae/file/file2_mem.hpp
	./solanaceae/file/file2_mem.cpp
)

target_include_directories(solanaceae_file2 PUBLIC .)
target_compile_features(solanaceae_file2 PUBLIC cxx_std_17)
target_link_libraries(solanaceae_file2 PUBLIC
	solanaceae_util
)
