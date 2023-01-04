#include <iostream>
#include <cxxopts.hpp>
#include "my_lib.h"
#include "config.hpp"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <fmt/format.h>

int main(int argc, char** argv){
    std::cout << project_name << std::endl;
    std::cout << project_version << std::endl;
    std::cout << "JSON PATCH VERSION " << NLOHMANN_JSON_VERSION_PATCH << std::endl;

    std::cout << "Info SPDLOG" << std::endl;
    spdlog::info("Welcome");
    auto welcome_message = fmt::format("Welcome to {} v{}\n", project_name, project_version);
    spdlog::info(welcome_message);

    cxxopts::Options options(project_name.data());
    options.add_options("arguments")("h,help", "Print Usage");

    auto result = options.parse(argc,argv);
    if (result.count("help"))
        std::cout << options.help() << '\n';
    print_hello_world();

    return 0;
}
