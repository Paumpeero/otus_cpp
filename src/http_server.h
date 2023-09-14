#pragma once
#include "sdk.h"
// boost.beast будет использовать std::string_view вместо boost::string_view
#define BOOST_BEAST_USE_STD_STRING_VIEW

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include "listener.h"
#include "session.h"

namespace http_server
{
template<typename RequestHandler>
void ServeHttp(net::io_context& ioc, const tcp::endpoint& endpoint, RequestHandler&& handler)
{
  using MyListener = Listener<std::decay_t<RequestHandler>>;

  std::make_shared<MyListener>(ioc, endpoint, std::forward<RequestHandler>(handler))->Run();
}
}
