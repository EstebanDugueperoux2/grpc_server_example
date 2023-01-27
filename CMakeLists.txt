cmake_minimum_required(VERSION 3.15)
project(grpc_server_example CXX)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif(CCACHE_FOUND)

#find_package(gRPC REQUIRED)
#find_package(protobuf_BUILD REQUIRED)
#find_package(gRPC_BUILD REQUIRED)

find_package(protobuf CONFIG REQUIRED)
find_package(protobuf_BUILD CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
# ugly hack to get the *build context* grpc plugin via gRPC::grpc_cpp_plugin
set(CMAKE_CROSSCOMPILING_orig ${CMAKE_CROSSCOMPILING})
set(CMAKE_CROSSCOMPILING FALSE)
find_package(gRPC_BUILD CONFIG REQUIRED)
set(CMAKE_CROSSCOMPILING ${CMAKE_CROSSCOMPILING_orig})

set(PROTO_FILES
    proto/address.proto
    proto/addressbook.proto
)

add_executable(grpc_server_example src/grpc_server_example.cpp src/main.cpp ${PROTO_FILES})
target_link_libraries(grpc_server_example
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
target_include_directories(grpc_server_example PUBLIC include ${CMAKE_CURRENT_BINARY_DIR}) 

#
# Compile protobuf and grpc files in myproto target to cpp
#
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET grpc_server_example LANGUAGE cpp)
protobuf_generate(TARGET grpc_server_example LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

set_target_properties(grpc_server_example PROPERTIES
  RESOURCE "${PROTO_FILES}")

install(TARGETS grpc_server_example RESOURCE DESTINATION res)