cmake_minimum_required(VERSION 3.13)

add_library(collection STATIC
    collection.c
    utils/coll_utils.c
)

target_include_directories(collection PRIVATE
    utils
    .
)

target_include_directories(collection PUBLIC
    port
    .
)

target_link_libraries(collection)
target_compile_options(collection PRIVATE -Wstack-usage=300)

add_sanitizers(collection)
set_strict_compiler_warnings(collection)
