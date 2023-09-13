#include "http_server.h"
#include "session_base.h"

#include <boost/asio/dispatch.hpp>
#include <iostream>

namespace http_server
{
void ReportError(beast::error_code ec, std::string_view what) {
  std::cerr << what << ": "sv << ec.message() << std::endl;
}
SessionBase::SessionBase(tcp::socket&& socket)
: stream_(std::move(socket))
{

}
void SessionBase::Run()
{

}
void SessionBase::Read()
{

}
}  // namespace http_server
