cmake_minimum_required(VERSION 3.23.0)
project(http-project VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(server server.cpp)
add_executable(client client.cpp)

add_library(libs INTERFACE)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(libs INTERFACE fmt::fmt)
find_package(httplib CONFIG REQUIRED)
target_link_libraries(libs INTERFACE httplib::httplib)


target_link_libraries(server PRIVATE libs)
target_link_libraries(client PRIVATE libs)

enable_testing()
add_subdirectory(test)

add_subdirectory(benchmark)

install(TARGETS server client DESTINATION bin)
# install(TARGETS $<TARGET_RUNTIME_DLLS:main> DESTINATION bin)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_NAME update_server_package)
include(CPack)

include(GNUInstallDirs)
