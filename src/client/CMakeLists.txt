set(target client)

add_executable(${target} src/main.cpp)
target_link_libraries(${target}
    PUBLIC
        proto
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

install(TARGETS ${target} RESOURCE DESTINATION bin)