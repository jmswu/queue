# C/C++ GTEST CMAKE-TEMPLATE #
### Introduction ###
* Cmake template for using GTest
* With cppcheck support (optional)
* With clang-tidy support (optional)
* With conan c/c++ package manager
* With Fake Function Framework (FFF)

### Depandancies ###
* [conan](https://conan.io/)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)

### Install depandancies ###
* Run `sudo apt install clang-tidy` to install clant-tidy
* Run `pip install conan` to installl conan
* Run `conan profile update settings.compiler.libcxx=libstdc++11 default` to use libcxx++11 if required. [reference](https://github.com/conan-io/conan/issues/2658)

### Installation ###
* Clone this repo with `git clone --recurse-submodules https://github.com/jmswu/cmake-template.git`
* Put test source files in `my_lib` folder
* Change `CppCheckSuppressions.txt` path to your path (optional, if using cppcheck)
* Edit `.clang-tidy` for the checks you use

### Build ###
* Run `mkdir build && cd build`
* Run `conan install ..` to install c/c++ library
* Run `cmake ..`
* Run `make`

### Run tests ###
* Run `cd build`
* Run `ctest` or `./bin/unit_test`

### Run checks ###
* Run `cd build` # must run under build folder
* Run `../run-check.sh` or `../run-check.sh | grep file_name`

