
############ Setup project and cmake
# Minimum cmake requirement. We should require a quite recent
# cmake for the dependency find macros etc. to be up to date.
cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
############ Paths

set(WEBSOCKETPP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(WEBSOCKETPP_INCLUDE ${WEBSOCKETPP_ROOT}/websocketpp)
set(WEBSOCKETPP_BUILD_ROOT ${CMAKE_CURRENT_BINARY_DIR})
set(WEBSOCKETPP_BIN ${WEBSOCKETPP_BUILD_ROOT}/bin)
set(WEBSOCKETPP_LIB ${WEBSOCKETPP_BUILD_ROOT}/lib)

# CMake install step prefix. I assume linux users want the prefix to
# be the default /usr or /usr/local so this is only adjusted on Windows.
# This must be set prior to any call to project or it will not be read correctly.
# - Windows: Build the INSTALL project in your solution file.
# - Linux/OSX: make install.
if(WIN32)
    set(CMAKE_INSTALL_PREFIX "${WEBSOCKETPP_ROOT}/install" CACHE PATH "")
endif()

############ Project name and version
set(WEBSOCKETPP_MAJOR_VERSION 1)
set(WEBSOCKETPP_MINOR_VERSION 0)
set(WEBSOCKETPP_PATCH_VERSION 0)
set(WEBSOCKETPP_VERSION ${WEBSOCKETPP_MAJOR_VERSION}.${WEBSOCKETPP_MINOR_VERSION}.${WEBSOCKETPP_PATCH_VERSION})

if(POLICY CMP0048)
  cmake_policy(GET CMP0048 _version_policy)
endif()

if(_version_allowed STREQUAL NEW)
  project(websocketpp VERSION ${WEBSOCKETPP_VERSION})
else()
  project(websocketpp)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/websocketpp)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute(needed later on)
foreach(p INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# Set CMake library search policy
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
    cmake_policy(SET CMP0005 NEW)
endif()

# Disable unnecessary build types
set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo;Debug" CACHE STRING "Configurations" FORCE)

# Include our cmake macros
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CMakeHelpers)

if(!WIN32)
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()
############  Build customization

# Override from command line "CMake -D<OPTION>=TRUE/FALSE/0/1/ON/OFF"
option(BUILD_EXAMPLES "Build websocketpp examples." TRUE)
option(BUILD_TESTS "Build websocketpp tests." FALSE)

if(BUILD_TESTS OR BUILD_EXAMPLES)

    enable_testing()

    ############ Compiler specific setup

    set(WEBSOCKETPP_PLATFORM_LIBS "")
    set(WEBSOCKETPP_PLATFORM_TLS_LIBS "")

    ############ Dependencies

    find_package(OpenSSL)
    find_package(ZLIB)
endif()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/asio/include)
############ Add projects

# Add main library
add_subdirectory(websocketpp)

# Add examples
if(BUILD_EXAMPLES)
    include_subdirs("examples")
endif()

# Add tests
if(BUILD_TESTS)
    include_subdirs("test")
endif()

print_used_build_config()

export(PACKAGE websocketpp)

include(CMakePackageConfigHelpers)
configure_package_config_file(websocketpp-config.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/websocketpp-config.cmake"
  PATH_VARS INSTALL_INCLUDE_DIR
  INSTALL_DESTINATION "${INSTALL_CMAKE_DIR}"
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file("${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/websocketpp-configVersion.cmake"
  VERSION ${WEBSOCKETPP_VERSION}
  COMPATIBILITY ExactVersion)

# Install the websocketpp-config.cmake and websocketpp-configVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/websocketpp-config.cmake"
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/websocketpp-configVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

