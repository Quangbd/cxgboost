rm -rf build
mkdir "build"
cd build
#cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_ENV=osx_x86_64 ..
cmake \
    -DCMAKE_TOOLCHAIN_FILE=/Users/quangbd/Library/Android/sdk/ndk/21.3.6528147/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DBUILD_ENV=arm64-v8a \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_NATIVE_API_LEVEL=28 ..
make -j4