#!/bin/sh

find_clang_tidy() {
    for clang_cmd in clang-tidy clang-tidy-13 clang-tidy-12 clang-tidy-11 clang-tidy-10; do
        $clang_cmd --version 1>/dev/null 2>&1 && echo -n "$clang_cmd" && break;
    done
}

find_clang() {
    for clang_cmd in clang clang-13 clang-12 clang-11 clang-10; do
        $clang_cmd -v 1>/dev/null 2>&1 && echo -n "$clang_cmd" && break;
    done
}

find_clangxx() {
    for clang_cmd in clang++ clang++-13 clang++-12 clang++-11 clang++-10; do
        $clang_cmd -v 1>/dev/null 2>&1 && echo -n "$clang_cmd" && break;
    done
}

CC="$(find_clang)"
CXX="$(find_clangxx)"
clang_tidy="$(find_clang_tidy)"

if [ -z "$CC" ] || [ -z "$CXX" ] || [ -z "$clang_tidy" ] ; then
    echo "failed to find clang tools."
    echo "clang cmd: ${CC}"
    echo "clang++ cmd: ${CXX}"
    echo "clang-tidy: ${clang_tidy}"
    exit 1;
fi

clear
rm -rf build
mkdir -p build
cd build
CXX="${CXX}" CC="${CC}" cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCOLLECTION_CONFIG_RUNTIME_CHECKS_ENABLED=On \
    -DCOLLECTION_BUILD_TESTS=On \
    -DSANITIZE_ADDRESS=On \
    -DSANITIZE_UNDEFINED=On \
    -DCMAKE_C_CLANG_TIDY="${clang_tidy}" \
    -DCMAKE_CXX_CLANG_TIDY="${clang_tidy}" 
make -j
cd ..
