call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake --version
mkdir .build
cd .build
rm -rf -- *
cmake ..
cmake --build .
ctest
cd ..
