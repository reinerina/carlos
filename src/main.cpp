#include <fstream>
#include <cxxopts.hpp>
#include <glog/logging.h>
#include "carlos.lex.h"
#include "carlos.parser.h"
#include "ast.h"
#include "table.h"
#include "gen.h"

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  auto options = std::make_unique<cxxopts::Options>(
      "calors", "A simple programming language compiler");

  auto &ops = *options;

  ops.set_width(70).add_options()                               //
      ("h,help", "Print help")                                  //
      ("i,input", "Input file", cxxopts::value<std::string>())  //
      ("m,mode", "Mode", cxxopts::value<std::string>())         //
      ("o,output", "Output file", cxxopts::value<std::string>());

  auto result = ops.parse(argc, argv);

  if (result.count("help")) {
    std::cout << ops.help() << std::endl;
    return 0;
  }

  if (result.count("input") == 0) {
    std::cerr << "No input file specified" << std::endl;
    std::cerr << "Please use -h or --help for more information" << std::endl;
    return 1;
  }

  auto path = result["input"].as<std::string>();

  auto file = std::ifstream(path);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << path << std::endl;
    return 1;
  }

  std::cin.rdbuf(file.rdbuf());
  auto lexer = carlos::CarlosLexer(std::cin);
  auto parser = carlos::CarlosParser(lexer);
  parser.parse();

  auto ast = carlos::ASTDisplay(carlos::root, 2);
  ast.print_ast();

  auto table = carlos::SymbolTable(carlos::root, false);
  table.process();

  auto gen = carlos::IRGen(carlos::root);

  if (result.count("output") == 0) {
    const auto output = path.substr(0, path.find_last_of('.')) + ".ll";
    auto output_file = std::ofstream(output);
    if (!file.is_open()) {
      std::cerr << "Failed to open file: " << output << std::endl;
      return 1;
    }
    const auto original = std::cout.rdbuf();
    std::cout.rdbuf(output_file.rdbuf());
    gen.gen();
    std::cout.rdbuf(original);
    output_file.close();
    file.close();
    return 0;
  }

  const auto output = result["output"].as<std::string>();
  auto output_file = std::ofstream(output);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << output << std::endl;
    return 1;
  }
  const auto original = std::cout.rdbuf();
  std::cout.rdbuf(output_file.rdbuf());
  gen.gen();
  std::cout.rdbuf(original);
  output_file.close();
  file.close();

  return 0;
}
