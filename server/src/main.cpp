#include <boost/program_options.hpp>

#include "tcp_server.h"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{

   try {
       unsigned short port;

       po::options_description description("Allowed options");
       description.add_options()("port", po::value<unsigned short>(&port)->default_value(8888), "TCP Server port number");

       po::variables_map vm;

       try {
           po::store(po::parse_command_line(argc, argv, description), vm);
           po::notify(vm);

           if (vm.count("port"))
           {
               std::cout << "Port: " << port << std::endl;
           }
       } catch (const po::error& e) {
           std::cerr << "Error: " << e.what() << std::endl;
           return EXIT_FAILURE;
       }

       boost::asio::io_context io_context;

       TcpServer server(io_context, port);

       io_context.run();

    } catch (const std::exception& e) {
       std::cerr << "Exception: " << e.what() << std::endl;
   }

    return EXIT_SUCCESS;
}