cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Primes VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Primes 
               src/main.cpp 
               src/primes.cpp
               src/prime_cache.cpp
               )

target_include_directories(Primes PUBLIC
                           "include"
                           )