#include <address.pb.h>
#include <addressbook.grpc.pb.h>

#include <grpc/grpc.h>

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class AddressBookService final : public expcmake::AddressBook::Service {
    public:
        virtual ::grpc::Status GetAddress(::grpc::ServerContext* context, const ::expcmake::NameQuerry* request, ::expcmake::Address* response)
        {
            std::cout << "Server: GetAddress for \"" << request->name() << "\"." << std::endl;

            response->set_name("Peter Peterson");
            response->set_zip("12345");
            response->set_country("Superland");
            
            return grpc::Status::OK;
        }
};

void grpc_server_example(){

    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

    AddressBookService my_service;
    builder.RegisterService(&my_service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
    
}
