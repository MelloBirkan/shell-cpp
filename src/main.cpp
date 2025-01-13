#include <iostream>
#include <string>
#include <sstream>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true) {
    std::cout << "$ ";

    std::string input;
    std::getline(std::cin, input);

    std::stringstream ss(input);
    std::string comando;
    std::string argumento;
    ss >> comando;
    std::getline(ss >> std::ws, argumento);
    
    if (input == "exit 0") {
      break;
    } else if (comando == "echo") {
      std::cout << argumento << "\n";
    } else {
      std::cout << input <<": command not found\n";
    }
  }
  return 0;
}

