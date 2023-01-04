cmake_minimum_required(VERSION 3.16)

project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C CXX)

#Creating variables to use them in subdirectories
set(LIBRARY_NAME Library)
set(EXECUTABLE_NAME Executable)


set(CMAKE_CXX_STANDARD 17)          # Setting C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Run just standard code.
set(CMAKE_CXX_EXTENSIONS OFF)       # Some extensions like variable length arrays in C are not allowed
set(CMAKE_BUILD_TYPE Debug)

option(ENABLE_TESTING "Wheather or not enable unit test tool" ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(AddGitSubmodule)
include(FetchContent) # Already defined in CMAKE scope
include(docs)

add_git_submodule(external/json)
# Cloning the repo
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 8.1.1
)
# Compiles the target
FetchContent_MakeAvailable(fmt)

# Cloning the repo
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.9.2
)
# Compiles the target
FetchContent_MakeAvailable(spdlog)


option(COMPILE_EXECUTABLE "Wheather to compiler the executable" ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(configured)
add_subdirectory(external)
add_subdirectory(src)
if(COMPILE_EXECUTABLE)
    add_subdirectory(app)
else()
    message("W/o exe compiling")
endif()
message("Compiled up to testing.")
add_subdirectory(test)
