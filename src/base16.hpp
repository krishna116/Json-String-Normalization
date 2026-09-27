#include <cstdint>
#include <string>

class base16 {
public:
  /**
   * Encode string to base16.
   * 
   * @param data  String data.
   * @param size  String size.
   * 
   * @return std::string  Encoded string.
   */
  static std::string encode(const char *data, std::size_t size) {
    static const char map[] = "0123456789ABCDEF";
    if (size == 0){
      return {};
    }
    std::string str;
    str.reserve(size << 1);
    for (std::size_t i = 0; i < size; ++i) {
      auto hi = static_cast<uint8_t>(data[i]) >> 4;
      auto lo = static_cast<uint8_t>(data[i]) & 0xF;
      str.push_back(map[hi]);
      str.push_back(map[lo]);
    }
    return str;
  }

  /**
   * Decode base16 string.
   * 
   * @param data  Encoded string data.
   * @param size  Encoded string size.
   * 
   * @return std::string  Decoded string.
   */
  static std::string decode(const char *data, std::size_t size) {
    auto remap = [](uint8_t c) {
      if ('0' <= c && c <= '9') {
        return c - '0';
      } else if ('A' <= c && c <= 'F') {
        return c - 'A' + 10;
      }
      return 0;
    };
    if (size & 1) {
      size -= 1;
    }
    if (size == 0) {
      return {};
    }
    std::string str;
    str.reserve(size >> 1);
    for (std::size_t i = 0; i < size; i += 2) {
      uint8_t value = remap(static_cast<uint8_t>(data[i])) << 4;
      value |= remap(data[i + 1]);
      str.push_back(static_cast<char>(value));
    }
    return str;
  }
};
