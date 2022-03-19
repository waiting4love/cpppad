#include <iostream>
#include <boost/asio.hpp>
#include <boost/regex.hpp>

using boost::asio::ip::tcp;
boost::asio::awaitable<void> echo(boost::asio::io_context &executor)
{
  try
  {
    tcp::socket socket(executor);
    co_await socket.async_connect({tcp::v4(), 55555}, boost::asio::use_awaitable); // 异步执行连接服务器

    char data[1024];
    for (;;)
    {
      std::size_t n = co_await socket.async_read_some(boost::asio::buffer(data), boost::asio::use_awaitable);
      co_await boost::asio::async_write(socket, boost::asio::buffer(data, n), boost::asio::use_awaitable);
    }
  }
  catch (std::exception &e)
  {
    std::printf("echo Exception: %s\n", e.what());
  }
}

int main()
{
  boost::asio::io_context executor(1);
  boost::asio::co_spawn(executor, echo(executor), boost::asio::detached);
  executor.run();
  return 0;
}