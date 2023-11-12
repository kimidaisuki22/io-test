#include <drogon/drogon.h>
#include <stdint.h>
#include <string>
using namespace drogon;
int main()
{
    const std::string address = "0.0.0.0";
    const uint16_t port = 12277;
    std::cout << "run on: http://" << address <<":" <<port <<"\n";
    app().setLogPath("./")
         .setLogLevel(trantor::Logger::kTrace)
         .addListener(address, port)
         .setThreadNum(0)
         .run();
}