#include <iostream>

#include "./generated/parser.tab.hh"

char fbuffer[(1 << 20) + 1];

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./ecc [path-to-file]" << std::endl;
    return 1;
  }
  parseFile(argv[1]);
  return 0;
}
