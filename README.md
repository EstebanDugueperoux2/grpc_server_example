# GRPC example using conan

```

```

## Steps to create a conan package with gcc8 profile

```
docker run --rm -ti -v ${PWD}:/home/conan/project conanio/gcc8-ubuntu18.04
cd project

conan create . --profile:build .conan/profiles/gcc8 --profile:host .conan/profiles/gcc8 --build missing
```

## Steps to create a conan package with cross compilation

```
docker run --rm -ti -v ${PWD}:/home/conan/project conanio/gcc8-ubuntu18.04
sudo apt -y update && sudo apt install -y crossbuild-essential-armhf
cd project

#docker run --rm -ti -v ${PWD}:/home/conan/project conanio/gcc9-armv7hf bash
#sudo pip install --upgrade conan

conan create . --profile:build .conan/profiles/gcc8 --profile:host .conan/profiles/linux-armv7hf-gcc7 --build missing
```

Draft of issue:

[ 14%] Building CXX object absl/random/CMakeFiles/random_internal_randen_hwaes_impl.dir/internal/randen_hwaes.cc.o
cc1plus: error: bad value ('armv8-a+crypto') for '-march=' switch
cc1plus: note: valid arguments to '-march=' switch are: nocona core2 nehalem corei7 westmere sandybridge corei7-avx ivybridge core-avx-i haswell core-avx2 broadwell skylake skylake-avx512 cannonlake icelake-client icelake-server bonnell atom silvermont slm knl knm x86-64 eden-x2 nano nano-1000 nano-2000 nano-3000 nano-x2 eden-x4 nano-x4 k8 k8-sse3 opteron opteron-sse3 athlon64 athlon64-sse3 athlon-fx amdfam10 barcelona bdver1 bdver2 bdver3 bdver4 znver1 btver1 btver2 native
absl/random/CMakeFiles/random_internal_randen_hwaes_impl.dir/build.make:62: recipe for target 'absl/random/CMakeFiles/random_internal_randen_hwaes_impl.dir/internal/randen_hwaes.cc.o' failed
make[2]: *** [absl/random/CMakeFiles/random_internal_randen_hwaes_impl.dir/internal/randen_hwaes.cc.o] Error 1
CMakeFiles/Makefile2:2005: recipe for target 'absl/random/CMakeFiles/random_internal_randen_hwaes_impl.dir/all' failed
make[1]: *** [absl/random/CMakeFiles/random_internal_randen_hwaes_impl.dir/all] Error 2
make[1]: *** Waiting for unfinished jobs....