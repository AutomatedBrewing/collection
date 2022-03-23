
# Unity CMakeLists did not seem to include the fixtures, so creating unity library here
add_library(unity STATIC
    Unity/src/unity.c
    Unity/extras/fixture/src/unity_fixture.c
    Unity/extras/memory/src/unity_memory.c)

target_include_directories(unity SYSTEM PUBLIC
    Unity/src
    Unity/extras/fixture/src
    Unity/extras/memory/src)

add_sanitizers(unity)
disable_static_check(unity)