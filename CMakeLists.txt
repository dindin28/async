cmake_minimum_required(VERSION 3.10)

project(async)

#========================
#Sources
#========================
file(GLOB srcs "*.cpp")

#========================
#Building executable
#========================
add_executable(${PROJECT_NAME} ${srcs})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)