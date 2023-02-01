cmake_minimum_required(VERSION 3.15)
project(grpc_server_example CXX)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif(CCACHE_FOUND)

find_package(gRPC REQUIRED)
find_package(protobuf_BUILD REQUIRED)
find_package(gRPC_BUILD REQUIRED)

# ugly hack to get the *build context* grpc plugin via gRPC::grpc_cpp_plugin
set(CMAKE_CROSSCOMPILING_orig ${CMAKE_CROSSCOMPILING})
set(CMAKE_CROSSCOMPILING FALSE)
find_package(gRPC_BUILD REQUIRED)
set(CMAKE_CROSSCOMPILING ${CMAKE_CROSSCOMPILING_orig})

set(PROTO_FILES
    ${CMAKE_CURRENT_LIST_DIR}/proto/address.proto
    ${CMAKE_CURRENT_LIST_DIR}/proto/addressbook.proto
)

# See https://github.com/protocolbuffers/protobuf/blob/main/docs/cmake_protobuf_generate.md

find_package(protobuf CONFIG REQUIRED)

add_library(proto-objects OBJECT "${PROTO_FILES}")

target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf gRPC::grpc++)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto")

target_include_directories(proto-objects PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(TARGET proto-objects IMPORT_DIRS ${PROTO_IMPORT_DIRS} PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")
protobuf_generate(TARGET proto-objects
        LANGUAGE grpc
        GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
        PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
        IMPORT_DIRS ${PROTO_IMPORT_DIRS}
        PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

add_executable(grpc_server_example src/grpc_server_example.cpp src/main.cpp)
target_link_libraries(grpc_server_example
    PUBLIC
        proto-objects
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
target_include_directories(grpc_server_example PUBLIC include ${CMAKE_CURRENT_BINARY_DIR}) 

# #
# # Compile protobuf and grpc files in myproto target to cpp
# #
# get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
# protobuf_generate(TARGET grpc_server_example LANGUAGE cpp)
# protobuf_generate(TARGET grpc_server_example LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

# set_target_properties(grpc_server_example PROPERTIES
#   RESOURCE "${PROTO_FILES}")

install(TARGETS grpc_server_example RESOURCE DESTINATION bin)