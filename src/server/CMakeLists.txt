set(target server)

add_executable(${target} src/grpc_server_example.cpp src/main.cpp)
target_link_libraries(${target}
    PUBLIC
        proto
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
target_include_directories(${target} PUBLIC include ${CMAKE_CURRENT_BINARY_DIR}) 

install(TARGETS ${target} RESOURCE DESTINATION bin)