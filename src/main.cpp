#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <unistd.h>

enum class Command {
    Echo,
    Exit,
    Type,
    Unknown
};

Command parseCommand(const std::string& cmd) {
    if (cmd == "echo") return Command::Echo;
    if (cmd == "exit") return Command::Exit;
    if (cmd == "type") return Command::Type;
    return Command::Unknown;
}

bool isExecutable(const std::string& path) {
    return access(path.c_str(), X_OK) == 0;
}

std::string findInPath(const std::string& command) {
    const char* pathEnv = std::getenv("PATH");
    if (!pathEnv) return "";
    
    std::string path(pathEnv);
    std::stringstream ss(path);
    std::string dir;
    
    while (std::getline(ss, dir, ':')) {
        std::string fullPath = dir + "/" + command;
        if (isExecutable(fullPath)) {
            return fullPath;
        }
    }
    return "";
}

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
    } else if (comando == "type") {
      if (parseCommand(argumento) != Command::Unknown) {
        std::cout << argumento << " is a shell builtin\n";
    } else {
        std::string path = findInPath(argumento);
        if (!path.empty()) {
            std::cout << argumento << " is " << path << "\n";
        } else {
            std::cout << argumento << ": not found\n";
        }
    }
  } else {
      std::cout << input <<": command not found\n";
    }
  }
  return 0;
}

