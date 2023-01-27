# GRPC example using conan

```

```

## Steps to create a conan package with gcc9 profile

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

conan create . --profile:build .conan/profiles/gcc8 --profile:host .conan/profiles/linux-armv7hf-gcc7 --build missing
```

Draft of issue:

Hi conan community,

In a Docker based CI context where I want to use minimal Docker images, i.e. a minimal size to avoid the overhead of image instantiation, I want to use cmake, ninja, ccache, protobuf and grpc, from my conan cache through a Docker volume.
Then I use conan tool_requires attribute as in https://github.com/EstebanDugueperoux2/grpc_server_example example.

In this example `conan create .` using both build and host profiles, add cmake from conan cache in the PATH to use it in the build:

```
docker run --rm -ti -v ${PWD}:/home/conan/project debian:bullseye
apt update
apt install -y gcc g++
apt install -y python3-pip
pip install conan
cd /home/conan/project

conan create . --profile:build .conan/profiles/gcc10 --profile:host .conan/profiles/gcc10 --build missing
```

But doing it in cross compilation case:

```
docker run --rm -ti -v ${PWD}:/home/conan/project debian:bullseye
apt update
apt install -y gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
apt install -y python3-pip
pip install conan
cd /home/conan/project

conan create . --profile:build .conan/profiles/gcc10 --profile:host .conan/profiles/linux-armv7hf-gcc10 --build missing
```

fails firstly on a cmake dependency `abseil` because this dependency needs cmake and haven't it in its tool_requires recipe attribute:

```
...
abseil/20220623.0: 
abseil/20220623.0: ERROR: Package '7eb25ef63e934a436f3acb1144cc28b376d3942f' build failed
...
```

Then my first question is could we advise to conan recipe mainteners to have if possible all the build tools used defined in tool_requires or the equivalent method (https://github.com/conan-io/conan-center-index/blob/master/docs/package_templates/cmake_package/all/conanfile.py#L102) to have these recipes more autonomous?
If yes, I can provide PR for abseil, gtest, ... .

I install temporarily cmake `apt install -y cmake` and I get this issue:

`/bin/sh: 1: /root/.conan/data/protobuf/3.21.4/_/_/package/6eac640ec9164ae7f9e2edf0bcb00e092769a96d/bin/protoc: Exec format error`

Then I apply https://docs.conan.io/en/latest/reference/conanfile/tools/cmake/cmakedeps.html#build-context-suffix

See https://github.com/conan-io/conan/issues/9494

Update conan center grpc and protobuf to be conan v2 ready and add tool_requires.

Regards.