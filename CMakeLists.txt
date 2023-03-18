cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Primes VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(compute 
               src/compute_primes.cpp 
               src/primes.cpp
               )

target_include_directories(compute PUBLIC
                           "include")