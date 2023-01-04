if(ENABLE_TESTING)
    set(TEST_MAIN "unit_tests")
    set(TEST_SOURCES "main.cpp")
    message("From Conan")
    message(CONAN_PKG::catch2)
    add_executable(${TEST_MAIN} ${TEST_SOURCES})
    target_link_libraries(${TEST_MAIN} PUBLIC
                            ${LIBRARY_NAME}
                            CONAN_PKG::catch2
                            )

endif()
