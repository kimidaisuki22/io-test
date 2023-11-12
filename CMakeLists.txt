cmake_minimum_required(VERSION 3.23.0)
project(io-test VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(io-test src/main.cpp)

find_package(fmt CONFIG REQUIRED)
find_package(cy CONFIG REQUIRED)
target_link_libraries(io-test PRIVATE fmt::fmt cy::cy)

target_include_directories(io-test PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

enable_testing()
add_subdirectory(test)

add_subdirectory(benchmark)

install(TARGETS io-test DESTINATION bin)
# install(TARGETS $<TARGET_RUNTIME_DLLS:main> DESTINATION bin)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_NAME update_server_package)
include(CPack)

include(GNUInstallDirs)
