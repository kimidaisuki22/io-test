#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cy/text/to_str.h>
#include <fstream>
#include <iostream>
#include <main/main.h>
#include <stdint.h>
#include <string>
#include <thread>

int main(int argc, char **argv) {
  std::string filename{};
  float size{};
  if (argc < 3) {
    std::cerr << "usage: filename filesize[GB]"
              << "\n";
    return 1;
  }

  filename = argv[1];
  size = std::stof(argv[2]) * 1024 * 1024 * 1024;
  std::atomic_int64_t write_size{};
  std::atomic_bool stop{};
  std::thread t{[&] {
    int time{};
    int64_t last_write{};
    while (!stop) {
      std::this_thread::sleep_for(std::chrono::seconds{1});
      time++;
      auto w = write_size.load();
      auto avg = cy::text::to_number_unit_SI(w * 1.0f / time);
      auto current_write = w - last_write;
      last_write = w;
      auto current = cy::text::to_number_unit_SI(current_write);
      std::cout << "Avg: " << avg << "/s "
                << "current: " << current << "/s " << time << " s"
                << " size: " << cy::text::to_number_unit_SI(w) << "\n";
    }
  }};
  static std::array<char, 1024 * 1024> buffer;
  std::fill(buffer.begin(), buffer.end(), '1');
  {
    std::ofstream file{filename, std::ios::binary};
    while (write_size < size) {
      write_size += buffer.size();
      file.write(buffer.data(), buffer.size());
    }
  }

  stop = true;
  t.join();
  return 0;
}
