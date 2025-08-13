# -S contains path to CMakeLists.txt
# -B is the build directory, will be automatically created
cmake -S. -B./build
cmake --build ./build
./build/queue
