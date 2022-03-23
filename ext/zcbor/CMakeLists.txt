add_library(zcbor STATIC
    zcbor/src/zcbor_common.c
    zcbor/src/zcbor_decode.c
    zcbor/src/zcbor_encode.c)

target_include_directories(zcbor SYSTEM PUBLIC
    zcbor/include)

#add_sanitizers(unity)
#disable_static_check(unity)