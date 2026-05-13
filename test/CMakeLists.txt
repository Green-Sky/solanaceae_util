cmake_minimum_required(VERSION 3.18...3.24 FATAL_ERROR)

project(solanaceae)

add_executable(solanaceae_util_bitset_test
	./bitset_tests.cpp
)

target_link_libraries(solanaceae_util_bitset_test PUBLIC
	solanaceae_util
)

add_test(NAME solanaceae_util_bitset_test COMMAND solanaceae_util_bitset_test)

########################################

add_executable(solanaceae_util_file_synced_test
	./test_file_synced.cpp
)

target_link_libraries(solanaceae_util_file_synced_test PUBLIC
	solanaceae_util
)

add_test(NAME solanaceae_util_file_synced_test COMMAND solanaceae_util_file_synced_test)
