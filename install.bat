mkdir build
cd build
cmake ..
cmake --build . --config Release --target install
cmake --build . --config Debug --target install
cd ..