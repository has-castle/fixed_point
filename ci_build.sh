cmake --version
mkdir -p .build
rm -rf -- *
cd .build
cmake -G Ninja ..
cmake --build .
ctest -C test
cd ..
