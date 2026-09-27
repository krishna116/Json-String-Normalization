#include <iostream>
#include <string>

#include "JsonSringNormalization.hpp"

int main() {
  std::string text = R"(begin-"""---{{{}}}\\\---'''---%%%-end)";
  auto encoded = JsonSringNormalization::encode(text);
  auto decoded = JsonSringNormalization::decode(encoded);

  std::cout <<"text    = " << text <<"\n";
  std::cout <<"encoded = " << encoded <<"\n";
  std::cout <<"decoded = " << decoded <<"\n";

  printf("\ntest result %s\n", text == decoded? "success.":"failed.");
  
  return text == decoded ? 0 : 1;
}
