# GRPC example using conan

```

```

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
grpc-proto/cci.20220627: Calling build()
grpc-proto/cci.20220627: 
grpc-proto/cci.20220627: ERROR: Package 'a7a777aaf7fbb80eead3cefb6f93d9f6a2e651b9' build failed
grpc-proto/cci.20220627: WARN: Build folder /home/conan/.conan/data/grpc-proto/cci.20220627/_/_/build/a7a777aaf7fbb80eead3cefb6f93d9f6a2e651b9
ERROR: grpc-proto/cci.20220627: Error in build() method, line 97
        cmake = self._configure_cmake()
while calling '_configure_cmake', line 63
        cmake.definitions["GOOGLEAPIS_PROTO_DIRS"] = self.dependencies["googleapis"].cpp_info.resdirs[0].replace("\\", "/")
        IndexError: list index out of range
```

Get issue of https://stackoverflow.com/questions/31698241/linking-error-when-compiling-crypto-for-armhf

To workaround that:

```
sudo ln -s /usr/ /usr/arm-linux-gnueabihf/usr
```
