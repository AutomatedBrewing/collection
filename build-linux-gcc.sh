clear
rm -rf build
mkdir -p build
cd build
CXX=g++ CC=gcc cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCOLLECTION_CONFIG_RUNTIME_CHECKS_ENABLED=On \
    -DCOLLECTION_BUILD_TESTS=On \
    -DSANITIZE_ADDRESS=On \
    -DSANITIZE_UNDEFINED=On \
    -DCOLL_ENABLE_COVERAGE=On
make -j
cd ..
