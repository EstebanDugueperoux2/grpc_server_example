cmake_minimum_required(VERSION 3.15)
project(grpc_server_example CXX)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif(CCACHE_FOUND)

add_subdirectory(proto)
add_subdirectory(src/server)
add_subdirectory(src/client)