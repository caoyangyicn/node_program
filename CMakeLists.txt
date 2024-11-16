cmake_minimum_required(VERSION 3.10)

# Define the project name and specify the C++ standard
project(HelloWorldProject VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(. include)

# Add the executable
file(GLOB SOURCES "src/*.cc")
add_executable(my_node ${SOURCES})

# add_executable(my_node src/main.cc src/my_file.cc src/util.cc)
link_directories(lib)

# Link the required libraries
target_link_libraries(my_node PRIVATE
    v8_monolith
    uv
    dl
    pthread
)

# Add compile definitions
target_compile_definitions(my_node PRIVATE
    V8_COMPRESS_POINTERS
    V8_ENABLE_SANDBOX
)

# Specify the linker
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fuse-ld=lld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${CMAKE_SOURCE_DIR}/lib -Wl,-rpath=${CMAKE_SOURCE_DIR}/lib")