# Add source files
file(GLOB_RECURSE SOURCES
    business/*.cpp
    file/*.cpp
    ui/*.cpp
    utility/*.cpp
)

# Create a library
add_library(WebScrappy ${SOURCES})

# Link the library to cURL
target_link_libraries(WebScrappy PRIVATE ${CURL_LIBRARIES})
