rd /s /q vs_build
mkdir vs_build
pushd vs_build
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=install ../
popd
