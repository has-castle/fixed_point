mkdir -p .build && \
cd .build && \
cmake -G Ninja .. && \
cmake --build . && \
ctest -C test && \
cd ..
