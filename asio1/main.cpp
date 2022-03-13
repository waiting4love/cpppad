#include <iostream>
#include <boost/asio.hpp>
#include <boost/regex.hpp>

int main()
{
    boost::regex reg{R"(\d{3})"};
    boost::cmatch mat;
    if(boost::regex_search("2sieu12345ss", mat, reg))
    {
        std::cout << mat.str() << std::endl;
    }

    boost::asio::io_context io;
    boost::asio::steady_timer t(io, std::chrono::seconds(5));
    t.async_wait([](auto err){
        std::cout << "Hello, ASIO!" << std::endl;
    });
    
    io.run();
    return 0;
}