cmake_minimum_required(VERSION 3.21)

project(linear_algebra
  VERSION 0.1.0
  DESCRIPTION "linear algebra library"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest)
include(CPack)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(LINEAR_ALGEBRA_BUILD_TESTS "Build tests" ${BUILD_TESTING})
option(LINEAR_ALGEBRA_BUILD_EXAMPLES "Build examples" OFF)
option(LINEAR_ALGEBRA_ENABLE_LTO "Enable Interprocedural Optimization" OFF)
option(LINEAR_ALGEBRA_ENABLE_ASAN "Enable Address Sanitizer" OFF)

add_library(${PROJECT_NAME} src/matrix.cpp src/vector.cpp)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(gcc_clang_warnings
  -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast
  -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion
  -Wdouble-promotion -Wformat=2
)

set(msvc_warnings
  /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /w14296 /w14311 /w14545
  /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928
)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${PROJECT_NAME} PRIVATE ${msvc_warnings})
else()
  target_compile_options(${PROJECT_NAME} PRIVATE ${gcc_clang_warnings})
endif()

if(LINEAR_ALGEBRA_ENABLE_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT lto_supported OUTPUT lto_output)
  if(lto_supported)
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()
endif()

if(LINEAR_ALGEBRA_ENABLE_ASAN AND NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address -fno-omit-frame-pointer)
  target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
endif()

if(LINEAR_ALGEBRA_BUILD_TESTS)
  enable_testing()
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  add_executable(test_vector tests/test_vector.cpp)
  target_link_libraries(test_vector PRIVATE ${PROJECT_NAME}::${PROJECT_NAME} GTest::gtest_main)
  add_test(NAME test_vector COMMAND test_vector)

  add_executable(test_matrix tests/test_matrix.cpp)
  target_link_libraries(test_matrix PRIVATE ${PROJECT_NAME}::${PROJECT_NAME} GTest::gtest_main)
  add_test(NAME test_matrix COMMAND test_matrix)
endif()

if(LINEAR_ALGEBRA_BUILD_EXAMPLES)
  add_executable(basic_usage examples/basic_usage.cpp)
  target_link_libraries(basic_usage PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})
endif()

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

write_basic_package_version_file(
  "${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake.in"
  "@PACKAGE_INIT@\n"
  "include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake\")\n"
  "check_required_components(${PROJECT_NAME})\n"
)

configure_package_config_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
