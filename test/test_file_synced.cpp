#include <solanaceae/util/file_synced.hpp>

#include <stdexcept>
#include <string_view>
#include <filesystem>
#include <iostream>

#define ASSERT(X) { const auto x = X; if (!x) { std::cerr << "Assert failed: " << x << "(" #X ")\n"; return 1; } }
#define ASSERT_EQ(X, Y) { const auto x = X; const auto y = Y; if (x != y) { std::cerr << "Assert failed: " << x << "(" #X ") == " << y << "(" #Y ")\n"; return 1; } }

int main(void) {
	const auto temp_dir = std::filesystem::temp_directory_path() / "file_synced_tests";

	std::filesystem::create_directories(temp_dir); // making sure
	ASSERT(std::filesystem::exists(temp_dir));
	std::cout << "test temp dir: " << temp_dir << "\n";

	const std::string_view data1{"test data :)"};

	const auto file_path = temp_dir/"test1.file";

	try {
		write_to_file_synced(file_path, reinterpret_cast<const uint8_t*>(data1.data()), data1.size());
	} catch (const std::runtime_error& e) {
		std::cerr << "exception thrown: " << e.what() << "\n";
		return 1;
	}

	ASSERT(std::filesystem::exists(file_path));
	ASSERT_EQ(std::filesystem::file_size(file_path), data1.size());

	std::filesystem::remove_all(temp_dir);

	return 0;
}
