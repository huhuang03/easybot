cd build32
cmake . -A win32
cmake --build . --config Release --target install
cmake --build . --config Debug --target install
cd ..