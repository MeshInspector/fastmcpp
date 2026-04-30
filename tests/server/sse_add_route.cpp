/// @file sse_add_route.cpp
/// @brief Verifies SseServerWrapper::add_route() registers custom HTTP routes that
/// coexist with the built-in /sse + /messages handlers on the same listener.

#include "fastmcpp/server/sse_server.hpp"
#include "fastmcpp/util/json.hpp"

#include <cassert>
#include <httplib.h>
#include <iostream>
#include <string>
#include <thread>

using fastmcpp::Json;
using fastmcpp::server::SseServerWrapper;

int main()
{
    std::cout << "SseServerWrapper::add_route integration test\n";
    std::cout << "============================================\n\n";

    // Handler is unused for this test (no JSON-RPC traffic) but must be present.
    auto handler = [](const Json&) -> Json { return Json::object(); };

    // Port 0 = OS-assigned, avoids conflicts with parallel tests.
    SseServerWrapper server(handler, "127.0.0.1", 0);

    server.add_route("GET", "/probe",
                     [](const httplib::Request&, httplib::Response& res)
                     { res.set_content("ok", "text/plain"); });

    server.add_route("POST", R"(/echo/(.+))",
                     [](const httplib::Request& req, httplib::Response& res) {
                         // matches[0] = whole path, matches[1] = first capture
                         const std::string suffix = req.matches.size() > 1 ? req.matches[1].str() : std::string{};
                         res.set_content(suffix, "text/plain");
                     });

    std::cout << "[1/3] Starting server on OS-assigned port...\n";
    if (!server.start())
    {
        std::cerr << "  [FAIL] server.start() returned false\n";
        return 1;
    }
    const int port = server.port();
    std::cout << "  Started on 127.0.0.1:" << port << "\n";

    httplib::Client client("127.0.0.1", port);
    client.set_connection_timeout(std::chrono::seconds(2));
    client.set_read_timeout(std::chrono::seconds(2));

    std::cout << "\n[2/3] GET /probe -> expect 200 \"ok\"\n";
    {
        auto res = client.Get("/probe");
        if (!res || res->status != 200 || res->body != "ok")
        {
            std::cerr << "  [FAIL] GET /probe: status=" << (res ? res->status : -1)
                      << " body=" << (res ? res->body : "<no response>") << "\n";
            server.stop();
            return 1;
        }
        std::cout << "  [PASS]\n";
    }

    std::cout << "\n[3/3] POST /echo/hello -> expect 200 \"hello\"\n";
    {
        auto res = client.Post("/echo/hello", "", "text/plain");
        if (!res || res->status != 200 || res->body != "hello")
        {
            std::cerr << "  [FAIL] POST /echo/hello: status=" << (res ? res->status : -1)
                      << " body=" << (res ? res->body : "<no response>") << "\n";
            server.stop();
            return 1;
        }
        std::cout << "  [PASS]\n";
    }

    server.stop();
    std::cout << "\n============================================\n";
    std::cout << "[OK] SseServerWrapper::add_route TEST PASSED\n";
    std::cout << "============================================\n";
    return 0;
}
