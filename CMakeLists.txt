# Set the project name
project(MyProject)
add_compile_options(-Wall -Wextra -Wpedantic)
# Add the executable
set(CMAKE_CXX_STANDARD 20)
add_executable(MyProject code.cpp)
