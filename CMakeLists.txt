cmake_minimum_required(VERSION 3.0)
project(xattr-test CXX)
add_executable(xattr-test xattr-test.cc)
set_property(TARGET xattr-test PROPERTY CXX_STANDARD 11)