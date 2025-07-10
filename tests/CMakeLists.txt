# Enable testing
enable_testing()

# Detect all test source files
file(GLOB TEST_SOURCES *.cpp)

foreach(test_file ${TEST_SOURCES})
    # Extract the file name without extension
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} WebScrappy ${CURL_LIBRARIES})
    target_include_directories(${test_name} PRIVATE ${PROJECT_SOURCE_DIR}/include)

    # Register the test so CTest can find it
    add_test(NAME ${test_name} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name})
endforeach()
