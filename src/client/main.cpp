#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include <address.pb.h>
#include <addressbook.pb.h>
#include <address.grpc.pb.h>
#include <addressbook.grpc.pb.h>

#include <grpc/grpc.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

int main(int argc, char** argv) {
{
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint specified by
    // the argument "--target=" which is the only expected argument.
    // We indicate that the channel isn't authenticated (use of
    // InsecureChannelCredentials()).
    std::string target_str;
    std::string arg_str("--target");
    if (argc > 1)
    {
        std::string arg_val = argv[1];
        size_t start_pos = arg_val.find(arg_str);
        if (start_pos != std::string::npos)
        {
            start_pos += arg_str.size();
            if (arg_val[start_pos] == '=')
            {
                target_str = arg_val.substr(start_pos + 1);
            }
            else
            {
                std::cout << "The only correct argument syntax is --target="
                          << std::endl;
                return 0;
            }
        }
        else
        {
            std::cout << "The only acceptable argument is --target=" << std::endl;
            return 0;
        }
    }
    else
    {
        target_str = "localhost:50051";
    }
    GreeterClient greeter(
        grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;

    return 0;
}
