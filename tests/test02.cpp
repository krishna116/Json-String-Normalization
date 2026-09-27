#include <iostream>
#include "base16.hpp"

int main() {
  std::string text = R"( !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~)";
  std::string encoded = base16::encode(text.data(), text.size());
  std::string decoded = base16::decode(encoded.data(), encoded.size());

  std::cout << "text    = {" << text << "}\n";
  std::cout << "encoded = {" << encoded << "}\n";
  std::cout << "decoded = {" << decoded << "}\n";

  printf("\n");
  printf("test result %s\n", text == decoded ? "success." : "failure.");

  return 0;
}