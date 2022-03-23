
enable_testing()
add_subdirectory("${PROJECT_SOURCE_DIR}/test/googletest" "test/googletest")
mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)
set_target_properties(gtest PROPERTIES FOLDER utest)
set_target_properties(gtest_main PROPERTIES FOLDER utest)
set_target_properties(gmock PROPERTIES FOLDER utest)
set_target_properties(gmock_main PROPERTIES FOLDER utest)

add_sanitizers(gtest)
add_sanitizers(gtest_main)
add_sanitizers(gmock)
add_sanitizers(gmock_main)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
    add_sanitizers(${TESTNAME})
endmacro()
