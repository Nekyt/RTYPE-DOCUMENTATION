mkdir -p build
cd vcpkg/
./bootstrap-vcpkg.sh
cd ../build/
cmake ..
make
cd ..
