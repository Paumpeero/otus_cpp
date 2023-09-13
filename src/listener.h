#pragma once
#include "sdk.h"
// boost.beast будет использовать std::string_view вместо boost::string_view
#define BOOST_BEAST_USE_STD_STRING_VIEW

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include "session.h"

namespace http_server
{
namespace net = boost::asio;
namespace sys = boost::system;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace http = beast::http;

template<typename RequestHandler>
class Listener : public std::enable_shared_from_this<Listener<RequestHandler>>
{
  net::io_context& ioc_;
  tcp::acceptor acceptor_;
  RequestHandler request_handler_;

 public:
  template<class Handler>
  Listener(net::io_context& ioc,
           const tcp::endpoint& endpoint,
           Handler&& request_handler)
    : ioc_(ioc),
      acceptor_(net::make_strand(ioc)),
      request_handler_(std::forward<Handler>(request_handler))
  {
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(net::socket_base::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen(net::socket_base::max_listen_connections);
  }

  void Run()
  {
    DoAccept();
  }

 private:
  void DoAccept()
  {
    acceptor_.async_accept(net::make_strand(ioc_),
                           beast::bind_front_handler(&Listener::DoAccept,
                                                     this->shared_from_this()));
  }

  void OnAccept(sys::error_code ec, tcp::socket socket)
  {
    if (ec)
    {
      return ReportError(ec, "accept"sv);
    }

    AsyncRunSession(std::move(socket));

    DoAccept();
  }

  void AsyncRunSession(tcp::socket&& socket)
  {
    std::make_shared<Session<RequestHandler>>(std::move(socket),
                                              request_handler_)->Run();
  }
};
}  // namespace http_server