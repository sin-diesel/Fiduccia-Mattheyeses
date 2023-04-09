#include "HGraphMod.hpp"

#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;

struct Options {
  fs::path inputFile;
  fs::path outputFile;
  bool modified;
  explicit operator bool () const {
    return fs::exists (inputFile);
  }
};

Options parseArgs(int argc , char** argv);

Options parseArgs(int argc, char** argv) {
  Options set;
  if (argc != 2) {
    std::cout << "Please select files: <bin> <fileIn>\n";
    return set;
  }
  std::string file = std::string(argv[1]);
  set.inputFile = fs::path(file);
  set.outputFile = fs::path(file + ".part.2");
  std::cout << "Input file: " << fs::absolute(set.inputFile) << "\nOutput file: "
  << fs::absolute(set.outputFile) << "\n";
  return set;
}

int main(int argc, char *argv[]) {
  Options settings = parseArgs(argc, argv);
  if (!settings) {
    std::cout << "FileIn wasn't found!";
    return 1;
  }

  std::ifstream File{settings.inputFile};
  std::ofstream OutFile{settings.outputFile};

  HGraph Graph{File};
  Partitions Prt{Graph};

  auto const Start = std::chrono::steady_clock::now();
  unsigned const Iterations = Algorithm(Graph, Prt);
  auto const End = std::chrono::steady_clock::now();

  OutFile << settings.inputFile.string() << ' ' << Graph.getEdges().size() << ' '
        << Graph.getVertices().size() << ' ' << Prt.getCost() << ' '
        << (End - Start).count()<< ' ' << Iterations << '\n';
  return 0;
}
