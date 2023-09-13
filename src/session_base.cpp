#include "http_server.h"
#include "session_base.h"

#include <boost/asio/dispatch.hpp>
#include <iostream>

namespace http_server
{
void ReportError(beast::error_code ec, std::string_view what) {
  std::cerr << what << ": "sv << ec.message() << std::endl;
}
}  // namespace http_server
