# Native XGBoost

The C++ XGBoost version for `PC` and `Android`.

```
git clone https://github.com/Quangbd/cxgboost.git
cd cxgboost
mkdir -p /libs/arm64-v8a
mkdir -p /libs/osx_x86_64
```

## Build

**1. XGBoost**

- Follow the document: [https://xgboost.readthedocs.io/en/latest/build.html](https://xgboost.readthedocs.io/en/latest/build.html)
- For `PC`

```
git clone --recursive https://github.com/dmlc/xgboost
cd xgboost
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_STATIC_LIB=ON ..
make -j$(nproc)
cp build/dmlc-core/libdmlc.a lib/libxgboost.a ${path}/cxgboost/libs/osx_x86_64/
```

- For `Android`

```
git clone --recursive https://github.com/dmlc/xgboost
cd xgboost
mkdir build
cd build
cmake \                                                                                                                                                                                                                                                                                                                            ✘ INT 10:07:50
   -DCMAKE_TOOLCHAIN_FILE=/Users/$(username)/Library/Android/sdk/ndk/21.3.6528147/build/cmake/android.toolchain.cmake \
   -DANDROID_ABI=arm64-v8a \
   -DCMAKE_BUILD_TYPE=Release \
   -DANDROID_NATIVE_API_LEVEL=28 -DBUILD_STATIC_LIB=ON ..
make -j$(nproc)
cp build/dmlc-core/libdmlc.a lib/libxgboost.a ${path}/cxgboost/libs/arm64-v8a/
```

- Copy header files

```
cp -r include/xgboost ${path}/cxgboost/includes
```

**2.Lib**

- For `PC`

```
cd cxgboost
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

- For `Android`

```
cd cxgboost
mkdir build
cd build
cmake \                                                                                                                                                                                                                                                                                                                            ✘ INT 10:07:50
   -DCMAKE_TOOLCHAIN_FILE=/Users/$(username)/Library/Android/sdk/ndk/21.3.6528147/build/cmake/android.toolchain.cmake \
   -DANDROID_ABI=arm64-v8a \
   -DCMAKE_BUILD_TYPE=Release \
   -DANDROID_NATIVE_API_LEVEL=28 ..
make -j$(nproc)
```