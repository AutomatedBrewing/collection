add_subdirectory(mock/slist)

set(MOCK_REPO_SOURCES
    collection_test.c
    mock/coll_port_fs_mock.c
    mock/coll_port_linked_list_mock.c
    mock/coll_port_mem_mock.c
    mock/coll_port_serializer_mock.c
    mock/serializer/serializer_pet_decode.c
    mock/serializer/serializer_pet_encode.c
    mock/utils/test_utils.c
    runner.c)

set(MOCK_REPO_INCLUDES
    mock
    mock/serializer
    mock/utils)
    

add_executable(coll_utest
    ${MOCK_REPO_SOURCES})

target_include_directories(coll_utest PRIVATE
        ${MOCK_REPO_INCLUDES})
    
add_test(coll_utest coll_utest)
target_link_libraries(coll_utest unity collection slist zcbor )
target_compile_options(coll_utest PRIVATE -Wstack-usage=512)

set_strict_compiler_warnings(coll_utest)
add_sanitizers(coll_utest)
