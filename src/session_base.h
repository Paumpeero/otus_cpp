#pragma once
#include "sdk.h"
// boost.beast будет использовать std::string_view вместо boost::string_view
#define BOOST_BEAST_USE_STD_STRING_VIEW

#include <iostream>
#include <string_view>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

namespace http_server {

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace http = beast::http;

using namespace std::literals;

void ReportError(beast::error_code ec, std::string_view what);

class SessionBase {
 protected:
  using HttpRequest = http::request<http::string_body>;

  ~SessionBase() = default;

 public:
  SessionBase(const SessionBase&) = delete;
  SessionBase& operator =(const SessionBase&) = delete;

 protected:
  explicit SessionBase(tcp::socket&& socket);

 private:
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;
  HttpRequest request_;
};
}  // namespace http_server