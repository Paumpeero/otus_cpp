#pragma once
#include "sdk.h"
// boost.beast будет использовать std::string_view вместо boost::string_view
#define BOOST_BEAST_USE_STD_STRING_VIEW

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include "session_base.h"

namespace http_server {

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace http = beast::http;

template <typename RequestHandler>
class Session : public SessionBase, public std::enable_shared_from_this<Session<RequestHandler>> {
  RequestHandler request_handler_;

 public:
  template<class Handler>
  Session(tcp::socket&& socket, Handler&& request_handler)
  : SessionBase(std::move(socket)), request_handler_(request_handler)
  {}

  std::shared_ptr<SessionBase> GetSharedThis() override
  {
    return this->shared_from_this();
  }

 private:
  void HandleRequest(HttpRequest&& request) override {}
};
}  // namespace http_server