#pragma once
#include "fastmcpp/export.hpp"
#include "fastmcpp/types.hpp"

#include <string>

namespace fastmcpp
{

struct FASTMCPP_API Settings
{
    std::string log_level{"INFO"};
    bool enable_rich_tracebacks{false};
    /// Default minimum log level for messages sent to MCP clients.
    /// Clients can override per-session via logging/setLevel.
    std::optional<std::string> client_log_level;
    /// Default transport type (parity with Python FASTMCP_TRANSPORT setting)
    std::optional<std::string> transport;

    static Settings from_env();
    static Settings from_json(const Json& j);
};

} // namespace fastmcpp
