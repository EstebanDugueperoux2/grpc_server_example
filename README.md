# GRPC example using conan

Inspired from https://grpc.io/docs/languages/cpp/basics/

## Steps to create a conan package with gcc8 profile

```
docker run --rm -ti -v ${PWD}:/home/conan/project conanio/gcc8-ubuntu18.04
cd project

conan create . --profile:build .conan/profiles/gcc8 --profile:host .conan/profiles/gcc8 --build missing -s grpc_server_example:build_type=Debug
```

## Steps to create a conan package with cross compilation

```
docker run --rm -ti -v ${PWD}:/home/conan/project conanio/gcc8-ubuntu18.04
sudo apt -y update && sudo apt install -y crossbuild-essential-armhf
cd project

conan create . --profile:build .conan/profiles/gcc8 --profile:host .conan/profiles/linux-armv7hf-gcc7 --build missing -s grpc_server_example:build_type=Debug
```

```
```

Get issue of https://stackoverflow.com/questions/31698241/linking-error-when-compiling-crypto-for-armhf

To workaround that:

```
sudo ln -s /usr/ /usr/arm-linux-gnueabihf/usr
```
