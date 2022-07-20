cmake_minimum_required(VERSION 3.15)
project(grpc_server_example CXX)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

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

# get_target_property(grpc_python_plugin_location gRPC::grpc_python_plugin LOCATION)
# protobuf_generate(TARGET grpc_server_example LANGUAGE python)
# protobuf_generate(TARGET grpc_server_example LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.py PLUGIN "protoc-gen-grpc=${grpc_python_plugin_location}")

set_target_properties(grpc_server_example PROPERTIES
  RESOURCE "${PROTO_FILES}")

install(TARGETS grpc_server_example RESOURCE DESTINATION res)