set(target server)

find_package(protobuf REQUIRED)
find_package(gRPC REQUIRED)

add_executable(${target} route_guide_server.cpp helper.cpp)
target_link_libraries(${target}
    PUBLIC
        proto
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
# target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}) 

install(TARGETS ${target} RESOURCE DESTINATION bin)