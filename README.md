# Paint in C

I wanted to get a nice look on C and WinAPI with this simple Paint project.

## Build instructions

1. `git clone https://github.com/AnanasikDev/CWINAPI`
2. open the directory, make a `build` subdirectory and go in it
3. `cmake -S ../ -G "YOUR_BUILD_TOOLCHAIN"` <- set the actual build toolchain you are going to use, for example `MinGW Makefiles` or `Visual Studio 17 2022`
4. `cd build & cmake --build .`