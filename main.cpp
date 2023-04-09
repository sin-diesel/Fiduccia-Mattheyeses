#include "HGraph.hpp"

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

Options parseArgs(int argc, char * argv[]) {
  Options set;
  if (argc != 2) {
    std::cout << "Please select files: <bin> <input_file>\n";
    return set;
  }
  std::string file = std::string(argv[1]);
  set.inputFile = fs::path(file);
  set.outputFile = fs::path(file + ".part.2");
  std::cout << "Input file: " << set.inputFile << "\nOutput file: "
  << set.outputFile << "\n";
  return set;
}

Options parseArgs (int argc , char** argv);

int main(int argc, char** argv) {
  Options Options = parseArgs(argc, argv);
  if (!Options) {
    std::cout << "Benchmark input file not found! Exiting...";
    return EXIT_FAILURE;
  }

  std::ifstream inputFile{Options.inputFile};
  std::ofstream outputFile{Options.outputFile};

  HGraph graph{inputFile};
  Partitions partition{graph};

  auto const Start = std::chrono::steady_clock::now();
  unsigned const Iterations = Algorithm(graph, partition);
  auto const End = std::chrono::steady_clock::now();

  outputFile << Options.inputFile.string() << ' ' << graph.getEdges().size() << ' '
        << graph.getVertices().size() << ' ' << partition.getCost() << ' '
        << (End - Start).count()<< ' ' << Iterations << '\n';
  return 0;
}
