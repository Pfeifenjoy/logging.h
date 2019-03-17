ls
rm -r build/
ls
cmake -H. -Bbuild/win64 --config Release           -DCMAKE_TOOLCHAIN_FILE=cmake/x86_64-w64-mingw32.cmake
cmake --config Release -H. -Bbuild/win64 -DCMAKE_TOOLCHAIN_FILE=cmake/x86_64-w64-mingw32.cmake
cmake --build build/win64/
ls build/
ls build/win64/
cmake --build build/win64/ --target package
apt install nsis
apt install nsis
cmake --build build/win64/ --target package
cd build/win64/
ls
tar xvf logging.h-Windows-master-584ac4a.zip 
unzip logging.h-Windows-master-584ac4a.zip 
apt install unzip
unzip logging.h-Windows-master-584ac4a.zip 
ls
ls logging.h-Windows-master-584ac4a
ls logging.h-Windows-master-584ac4a/lib/
ls logging.h-Windows-master-584ac4a/include/
cmake --build .
cmake --build .
ls
cd ..
cd ..
rm -rf build/
ls
cmake --config Release -H. -Bbuild/win64 -DCMAKE_TOOLCHAIN_FILE=cmake/x86_64-w64-mingw32.cmake
cmake --build build/win64/
cd build/win64/
ls
cmake --build . --target package
ls
apt install wine
apt install ninja
ls
wine logging.h-Windows-master-584ac4a.exe 
cd
ls
ls -lisa
rm -r .cache/
rm -r .bash_history 
rm -r .viminfo 
rm -r .wine/
ls
exit
