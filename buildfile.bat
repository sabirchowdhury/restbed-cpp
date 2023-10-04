del build\CMakeCache.txt
cmake -Bbuild -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --target ALL_BUILD --config Release
call build\Release\restbedcpp.exe