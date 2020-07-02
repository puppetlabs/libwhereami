cmake_minimum_required(VERSION 3.2.2)
project(whereami VERSION 0.2.5)

string(MAKE_C_IDENTIFIER ${PROJECT_NAME} PROJECT_C_NAME)
string(TOUPPER ${PROJECT_C_NAME} PROJECT_NAME_UPPER)
string(TOLOWER ${PROJECT_C_NAME} PROJECT_NAME_LOWER)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Defaulting to a release build.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

enable_testing()

# Leatherman setup
SET(LEATHERMAN_COMPONENTS locale catch nowide logging util file_util execution)

if (WIN32)
    list(APPEND LEATHERMAN_COMPONENTS windows)
endif()

find_package(Leatherman REQUIRED COMPONENTS ${LEATHERMAN_COMPONENTS})

# Pull in leatherman options
include(options)
## Pull in common cflags setting from leatherman. Don't override CMAKE_CXX_FLAGS at the project root to avoid impacting 3rd party code.
include(cflags)
set(${PROJECT_NAME_UPPER}_CXX_FLAGS "${LEATHERMAN_CXX_FLAGS}")
add_definitions(${LEATHERMAN_DEFINITIONS})

if(LEATHERMAN_USE_LOCALES)
    add_definitions(-DLEATHERMAN_I18N)
    set(BOOST_COMPONENTS locale)
endif()

## Pull in helper macros for working with leatherman libraries
include(leatherman)

list(APPEND BOOST_COMPONENTS filesystem regex system thread)

# Add other dependencies
find_package(Boost 1.54 REQUIRED COMPONENTS ${BOOST_COMPONENTS})

find_package(Threads)

# Display a summary of the features
include(FeatureSummary)
feature_summary(WHAT ALL)

file(GLOB_RECURSE ALL_SOURCES lib/src/*.cc lib/inc/*.hpp)
add_subdirectory(lib)
add_subdirectory(locales)

# Add cpplint and cppcheck targets
add_cpplint_files(${ALL_SOURCES})
enable_cpplint()

add_cppcheck_dirs("${PROJECT_SOURCE_DIR}/lib")
enable_cppcheck()
