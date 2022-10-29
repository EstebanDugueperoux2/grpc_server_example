from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout


class GrpcServerExampleConan(ConanFile):
    name = "grpc_server_example"
    version = "0.0.1"

    # Optional metadata
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of GrpcServerExample here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    requires = "grpc/1.50.0", "zlib/1.2.13" #zlib overriden to avoid conflict between grpc and protobuf
    #"gtest/[~1.11.0]"
    tool_requires = "cmake/3.24.2", "ninja/1.11.1", "ccache/4.6", "grpc/1.50.0", "protobuf/3.21.4"
    build_policy = "missing"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "proto/*"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()

        deps = CMakeDeps(self)
        # Usefull in case of cross compilation, see https://docs.conan.io/en/latest/reference/conanfile/tools/cmake/cmakedeps.html#build-context-activated
        deps.build_context_activated = ["cmake", "ninja", "ccache", "protobuf", "grpc"]
        deps.build_context_build_modules = ["protobuf", "grpc"]
        # Usefull in case of cross compilation, see https://docs.conan.io/en/latest/reference/conanfile/tools/cmake/cmakedeps.html#build-context-suffix
        # To avoid ".conan/data/protobuf/3.21.4/_/_/package/6eac640ec9164ae7f9e2edf0bcb00e092769a96d/bin/protoc: Exec format error`" errot
        deps.build_context_suffix = {"protobuf": "_BUILD", "grpc": "_BUILD"}
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build(cli_args=["--verbose"])

    def package(self):
        cmake = CMake(self)
        cmake.install()

    # def package_info(self):
    #     self.cpp_info.resdirs = ['proto']