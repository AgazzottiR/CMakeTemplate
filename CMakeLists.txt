cmake_minimum_required(VERSION 3.16)

project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C CXX)


#Global CMake Variables
set(CMAKE_CXX_STANDARD 17)          # Setting C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Run just standard code.
set(CMAKE_CXX_EXTENSIONS OFF)       # Some extensions like variable length arrays in C are not allowed
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)


#Optoions
option(USE_CONAN            "Whether to use conan or vcpkg"         ON)
option(ENABLE_TESTING "Wheather or not enable unit test tool" ON)
option(ENABLE_WARNINGS      "Enable to add warnings to a target."   ON)
option(ENABLE_TESTING       "Enable a Unit Testing build."          ON)
option(ENABLE_COVERAGE      "Enable a Code Coverage build."         OFF)
option(ENABLE_CLANG_TIDY    "Enable to add clang tidy."             OFF)
option(ENABLE_CPPCHECK      "Enable to add cppcheck."               OFF)
option(ENABLE_LTO           "Enable to add Link Time Optimization." OFF)
option(ENABLE_CCACHE        "Enable to add Ccache."                 OFF)
option(COMPILE_EXECUTABLE "Wheather to compiler the executable" ON)

#Project/Library Names
set(LIBRARY_NAME Library)
set(EXECUTABLE_NAME Executable)


### CMAKE MODULES
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(ConfigSafeGuards)
include(AddGitSubmodule)
include(Warnings)
include(FetchContent) # Already defined in CMAKE scope
include(docs)

include(StaticAnalyzer)
include(LTO) # Linker time optimization
include(Ccache)

if (ENABLE_TESTING)
    include(CTest)
    endif()

if (ENABLE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

if (ENABLE_LTO)
    find_lto(CXX)
endif()


### EXTERNAL LIBRARIES
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


if(USE_CONAN)
    message("Using Conan")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
else()
    # Note: VCPKG need more adaptations in cmake files
    # Also, rename the _vcpkg.json file to vcpkg.json
    message("Using VCPKG")
    find_package(Catch2 CONFIG REQUIRED)
    find_package(cxxopts CONFIG REQUIRED)
endif()


### SUB DIRECTORIES
add_subdirectory(configured)
add_subdirectory(external)
add_subdirectory(src)
if(COMPILE_EXECUTABLE)
    add_subdirectory(app)
else()
    message("W/o exe compiling")
endif()
add_subdirectory(test)

### INSTALL TARGETS
install(TARGETS ${EXECUTABLE_NAME}
        EXPORT ${LIBRARY_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(TARGETS ${LIBRARY_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
