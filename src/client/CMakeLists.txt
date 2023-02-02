set(target client)

find_package(protobuf REQUIRED)
find_package(gRPC REQUIRED)

add_executable(${target} route_guide_client.cpp helper.cpp)
target_link_libraries(${target}
    PUBLIC
        proto
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

install(TARGETS ${target} RESOURCE DESTINATION bin)