set(EXE_SOURCES
    "main.cpp")

add_executable(${EXECUTABLE_NAME} ${EXE_SOURCES})

# Linking the executables with the libraries
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
${LIBRARY_NAME}
nlohmann_json
fmt::fmt
spdlog::spdlog_header_only
CONAN_PKG::cxxopts)
