#pragma once

#include <cstdint>
#include <cstdlib>
#include <filesystem>

// simple function that tries ot avoid system buffer or flush to device after the write
void write_to_file_synced(const std::filesystem::path& file_path, const uint8_t* data, size_t data_size);

