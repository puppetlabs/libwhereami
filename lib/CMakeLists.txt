include(leatherman)
get_commit_string(PROJECT_COMMIT)

# Generate a file containing the above version numbers.
configure_file("version.h.in" "${CMAKE_CURRENT_LIST_DIR}/inc/${PROJECT_NAME}/version.h")

# Generate files for Doxygen
configure_file("Doxyfile.in"       "${CMAKE_CURRENT_LIST_DIR}/Doxyfile")
configure_file("namespaces.dox.in" "${CMAKE_CURRENT_LIST_DIR}/docs/namespaces.dox")

# Set C++ compile flags based on project settings.
set(CMAKE_CXX_FLAGS ${${PROJECT_NAME_UPPER}_CXX_FLAGS})

# Set prefix for logging messages.
leatherman_logging_namespace("puppetlabs.${PROJECT_NAME}")

# Setup compiling the library.
include_directories(inc ${Boost_INCLUDE_DIRS} ${LEATHERMAN_INCLUDE_DIRS})

set(PROJECT_SOURCES
    "src/${PROJECT_NAME}.cc"
    "src/detectors/openvz_detector.cc"
    "src/detectors/docker_detector.cc"
    "src/detectors/hyperv_detector.cc"
    "src/detectors/kvm_detector.cc"
    "src/detectors/lpar_detector.cc"
    "src/detectors/lxc_detector.cc"
    "src/detectors/nspawn_detector.cc"
    "src/detectors/virtualbox_detector.cc"
    "src/detectors/vmware_detector.cc"
    "src/detectors/wpar_detector.cc"
    "src/detectors/xen_detector.cc"
    "src/detectors/zone_detector.cc"
    "src/metadata.cc"
    "src/result.cc"
    "src/sources/cgroup_source.cc"
    "src/sources/cpuid_source.cc"
    "src/sources/dmi_source.cc"
    "src/sources/lparstat_source.cc"
    "src/sources/smbios_base.cc"
    "src/sources/system_profiler_source.cc")

if(WIN32)
    set(PROJECT_SOURCES ${PROJECT_SOURCES} "src/sources/wmi_source.cc")
endif()

## An object target is generated that can be used by both the library and test executable targets.
## Without the intermediate target, unexported symbols can't be tested.
add_library(libprojectsrc OBJECT ${PROJECT_SOURCES})
set_target_properties(libprojectsrc PROPERTIES POSITION_INDEPENDENT_CODE true)

add_library(lib${PROJECT_NAME} $<TARGET_OBJECTS:libprojectsrc>)
set_target_properties(lib${PROJECT_NAME} PROPERTIES VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
target_link_libraries(lib${PROJECT_NAME}
    ${LEATHERMAN_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

symbol_exports(lib${PROJECT_NAME} "${CMAKE_CURRENT_LIST_DIR}/inc/${PROJECT_NAME}/export.h")

leatherman_install(lib${PROJECT_NAME})
install(DIRECTORY inc/${PROJECT_NAME} DESTINATION include)

add_subdirectory(tests)
