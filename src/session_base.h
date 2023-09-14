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

  void Run();
  void Read();

  virtual std::shared_ptr<SessionBase> GetSharedThis() = 0;

 protected:
  explicit SessionBase(tcp::socket&& socket);

  template <typename Body, typename Fields>
  void Write(http::response<Body, Fields>&& response) {
    // Запись выполняется асинхронно, поэтому response перемещаем в область кучи
    auto safe_response = std::make_shared<http::response<Body, Fields>>(std::move(response));

    auto self = GetSharedThis();
    http::async_write(stream_, *safe_response,
                      [safe_response, self](beast::error_code ec, std::size_t bytes_written) {
                        self->OnWrite(safe_response->need_eof(), ec, bytes_written);
                      });
  }

 private:
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;
  HttpRequest request_;

  void OnRead(beast::error_code ec, [[maybe_unused]] size_t bytes_read);

  void Close();

  virtual void HandleRequest(HttpRequest&& request) = 0;

  void OnWrite(bool close, beast::error_code ec, [[maybe_unused]] std::size_t bytes_written);
};
}  // namespace http_server