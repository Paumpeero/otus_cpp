#include "src/sdk.h"
//
#include <boost/asio/signal_set.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "src/http_server.h"

namespace
{
namespace net = boost::asio;
using namespace std::literals;
namespace sys = boost::system;
namespace http = boost::beast::http;
using namespace std;
using net::ip::tcp;

// Запрос, тело которого представлено в виде строки
using StringRequest = http::request<http::string_body>;
// Ответ, тело которого представлено в виде строки
using StringResponse = http::response<http::string_body>;

struct content_type
{
  content_type() = delete;
  constexpr static std::string_view k_TextHTML = "text/html"sv;
  // При необходимости внутрь content_type можно добавить и другие типы контента
};

// Создаёт StringResponse с заданными параметрами
StringResponse MakeStringResponse(http::status status,
                                  std::string_view body,
                                  unsigned http_version,
                                  bool keep_alive,
                                  std::string_view content_type = content_type::k_TextHTML)
{
  StringResponse response(status, http_version);
  response.set(http::field::content_type, content_type);
  response.body() = body;
  response.content_length(body.size());
  response.keep_alive(keep_alive);
  return response;
}

StringResponse HandleRequest(StringRequest&& req)
{
  auto route = req.target();

  return MakeStringResponse(http::status::ok,
                            "Hello, World!"sv,
                            req.version(),
                            req.keep_alive());
}

// Запускает функцию fn на n потоках, включая текущий
template<typename Fn>
void RunWorkers(unsigned n, const Fn& fn)
{
  n = std::max(1u, n);
  std::vector<std::jthread> workers;
  workers.reserve(n - 1);
  // Запускаем n-1 рабочих потоков, выполняющих функцию fn
  while (--n)
  {
    workers.emplace_back(fn);
  }
  fn();
}

}  // namespace

int main()
{
  const unsigned num_threads = std::thread::hardware_concurrency();

  net::io_context ioc(num_threads);
  tcp::acceptor   acceptor(net::make_strand(ioc));

  // Подписываемся на сигналы и при их получении завершаем работу сервера
  net::signal_set signals(ioc, SIGINT, SIGTERM);
  signals.async_wait([&ioc](const sys::error_code& ec,
                            [[maybe_unused]] int signal_number)
                     {
                       if (!ec)
                       {
                         cout << "Signal "sv << signal_number << " received"sv
                              << endl;
                         ioc.stop();
                       }
                     });

  const auto                   address = net::ip::make_address("0.0.0.0");
  constexpr net::ip::port_type port    = 8080;
  http_server::ServeHttp(ioc, {address, port}, [](auto&& req, auto&& sender)
  {
    sender(HandleRequest(std::forward<decltype(req)>(req)));
  });

  net::steady_timer t {ioc, 30s};

  t.async_wait([](sys::error_code ec)
               {
                 cout << "Timer expired"sv << endl;
               });

  std::cout << "Server has started..."sv << std::endl;

  RunWorkers(num_threads, [&ioc]
  {
    ioc.run();
  });
}
