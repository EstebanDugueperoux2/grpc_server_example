#pragma once

#ifdef _WIN32
  #define grpc_server_example_EXPORT __declspec(dllexport)
#else
  #define grpc_server_example_EXPORT
#endif

grpc_server_example_EXPORT void grpc_server_example();
