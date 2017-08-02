# Setup compiling the test executable. C++ compile flags are inherited from the parent directory.
include_directories(${LEATHERMAN_CATCH_INCLUDE})

set(TEST_CASES
    "${PROJECT_NAME}.cc"
    "detectors/metadata.cc"
    "detectors/openvz_detector.cc"
    "detectors/result.cc"
    "detectors/docker_detector.cc"
    "detectors/kvm_detector.cc"
    "detectors/lxc_detector.cc"
    "detectors/nspawn_detector.cc"
    "detectors/virtualbox_detector.cc"
    "detectors/vmware_detector.cc"
    "fixtures.cc"
    "fixtures/cpuid_fixtures.cc"
    "fixtures/dmi_fixtures.cc"
    "sources/cgroup_source.cc"
    "sources/cpuid_source.cc"
    "sources/dmi_source.cc")

add_executable(lib${PROJECT_NAME}_test $<TARGET_OBJECTS:libprojectsrc> ${TEST_CASES} main.cc)
target_link_libraries(lib${PROJECT_NAME}_test
    ${Boost_LIBRARIES}
    ${LEATHERMAN_LIBRARIES}
)

add_test(NAME "unit_tests" COMMAND lib${PROJECT_NAME}_test)

# Generate a file containing the path to the fixtures
configure_file("fixtures.hpp.in" "${CMAKE_CURRENT_LIST_DIR}/fixtures.hpp")
