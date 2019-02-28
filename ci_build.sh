mkdir -p .build && \
cmake -G Ninja -S . -B .build && \
cmake --build .build && \
cd .build && \
ctest -C test && \
cd ..
