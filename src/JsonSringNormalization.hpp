#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

//
// JsonSringNormalization.
//
class JsonSringNormalization {
public:
  /**
   * Encode string.
   * 
   * @param in            The original string.
   * @return std::string  The encoded string.
   */
  static std::string encode(const std::string& in) {
    static const char kHexDigits[16 + 1] = "0123456789ABCDEF";
    std::string out;
    std::size_t length = in.size();
    for (std::size_t i = 0; i < length; ++i) {
      const unsigned char c = static_cast<unsigned char>(in[i]);
      if (isSafe(c)) {
        out.push_back(static_cast<char>(c));
      } else {
        out.push_back('%');
        out.push_back(kHexDigits[c >> 4]);
        out.push_back(kHexDigits[c & 0x0F]);
      }
    }
    return out;
  }

  /**
   * Decode string.
   * 
   * @param in            The encoded string.
   * @return std::string  The decoded string.
   */
  static std::string decode(const std::string& in) {
    std::string out;
    std::size_t length = in.size();
    std::size_t i = 0;
    // error.clear();
    while (i < length) {
      const unsigned char c = static_cast<unsigned char>(in[i]);
      if (c == '%') {
        if (i + 2 >= length){
          // error = toErrorStr("Fewer than two digits after '%'.", i);
          return out;
        }
        const int hi = hexValue(in[i + 1]);
        const int lo = hexValue(in[i + 2]);
        if (hi < 0 || lo < 0){
          // error = toErrorStr("Invalid hexadecimal.", i);
          return out;
        }
        out.push_back(static_cast<char>((hi << 4) | lo));
        i += 3;
      } else if (isSafe(c)) {
        out.push_back(static_cast<char>(c));
        i += 1;
      } else {
        // error = toErrorStr(i, "The encoded string must not contain ");
        // error += "'\"', '\\', control characters, or non-ASCII characters";
        return out;
      }
    }
    return out;
  }

  /**
   * Decode string with error report.
   * 
   * @param in            The encoded string.
   * @param error         Error report.
   * 
   * @return std::string  The decoded string.
   */
  std::string decode(const std::string& in, std::string& error) {
    std::string out;
    std::size_t length = in.size();
    std::size_t i = 0;
    error.clear();
    while (i < length) {
      const unsigned char c = static_cast<unsigned char>(in[i]);
      if (c == '%') {
        if (i + 2 >= length){
          error = toErrorStr(i, "Fewer than two digits after '%'.");
          return out;
        }
        const int hi = hexValue(in[i + 1]);
        const int lo = hexValue(in[i + 2]);
        if (hi < 0 || lo < 0){
          error = toErrorStr(i, "Invalid hexadecimal.");
          return out;
        }
        out.push_back(static_cast<char>((hi << 4) | lo));
        i += 3;
      } else if (isSafe(c)) {
        out.push_back(static_cast<char>(c));
        i += 1;
      } else {
        error = toErrorStr(i, "The encoded string must not contain ");
        error += "'\"', '\\', control characters, or non-ASCII characters";
        return out;
      }
    }
    return out;
  }

private:
  static std::string toErrorStr(const std::size_t& i, const std::string& msg){
    return "[index:" + std::to_string(i) + "] " + msg;
  }

  static bool isSafe(unsigned char c) {
    if (c < 0x20 || c > 0x7E)
      return false;
    if (c == '"' || c == '\\' || c == '%')
      return false;
    return true;
  }

  static int hexValue(char c) {
    if (c >= '0' && c <= '9')
      return c - '0';
    if (c >= 'A' && c <= 'F')
      return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
      return c - 'a' + 10;
    return -1;
  }
};
