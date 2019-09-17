cmake_minimum_required(VERSION 3.12)
project("GraphSearch" VERSION 2.0
  DESCRIPTION "A header only C++ library that provides implementations of common graph search algorithms."
  HOMEPAGE_URL "https://github.com/barulicm/CPPGraphSearch")

enable_testing()

include(GNUInstallDirs)

add_subdirectory(externals/Catch2)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/Catch2/contrib")

include(CTest)
include(Catch)

#
# Library definition
#

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

#
# Testing directives
#
add_executable(${PROJECT_NAME}_Tests
  tests/main.cpp
  tests/dfs/dfs_basic_tests.cpp
  tests/bfs/bfs_basic_tests.cpp
  tests/astar/astar_basic_tests.cpp)
target_link_libraries(${PROJECT_NAME}_Tests ${PROJECT_NAME} Catch2::Catch2)
catch_discover_tests(${PROJECT_NAME}_Tests)

#
# Examples
#
add_executable(11x11grid examples/11x11grid/main.cpp)
target_link_libraries(11x11grid ${PROJECT_NAME})

#
# Installation directives
#

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}_Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(EXPORT ${PROJECT_NAME}_Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(FILES
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/GraphSearch DESTINATION include)
