# Setup compiling the test executable. C++ compile flags are inherited from the parent directory.
include_directories(${LEATHERMAN_CATCH_INCLUDE})

set(TEST_CASES
    "${PROJECT_NAME}.cc"
    "detectors/openvz_detector.cc"
    "detectors/docker_detector.cc"
    "detectors/hyperv_detector.cc"
    "detectors/kvm_detector.cc"
    "detectors/ldom_detector.cc"
    "detectors/lpar_detector.cc"
    "detectors/lxc_detector.cc"
    "detectors/nspawn_detector.cc"
    "detectors/virtualbox_detector.cc"
    "detectors/vmware_detector.cc"
    "detectors/wpar_detector.cc"
    "detectors/xen_detector.cc"
    "detectors/zone_detector.cc"
    "fixtures.cc"
    "fixtures/cpuid_fixtures.cc"
    "fixtures/dmi_fixtures.cc"
    "metadata.cc"
    "result.cc"
    "sources/cgroup_source.cc"
    "sources/cpuid_source.cc"
    "sources/dmi_source.cc"
    "sources/lparstat_source.cc"
    "sources/system_profiler_source.cc")

add_executable(lib${PROJECT_NAME}_test $<TARGET_OBJECTS:libprojectsrc> ${TEST_CASES} main.cc)
target_link_libraries(lib${PROJECT_NAME}_test
    ${Boost_LIBRARIES}
    ${LEATHERMAN_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND BOOST_STATIC AND LEATHERMAN_USE_LOCALES)
    target_link_libraries(lib${PROJECT_NAME}_test iconv)
endif()

add_test(NAME "unit_tests" COMMAND lib${PROJECT_NAME}_test)

# Generate a file containing the path to the fixtures
configure_file("fixtures.hpp.in" "${CMAKE_CURRENT_LIST_DIR}/fixtures.hpp")
