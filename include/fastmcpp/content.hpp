#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace fastmcpp
{

using Json = nlohmann::json;

struct TextContent
{
    std::string type{"text"};
    std::string text;
};

struct ImageContent
{
    std::string type{"image"};
    std::string data;     // base64-encoded image bytes
    std::string mimeType; // e.g., "image/png"
};

struct AudioContent
{
    std::string type{"audio"};
    std::string data;     // base64-encoded audio bytes
    std::string mimeType; // e.g., "audio/wav", "audio/mpeg", "audio/ogg"
};

// nlohmann::json adapters
inline void to_json(Json& j, const TextContent& c)
{
    j = Json{{"type", c.type}, {"text", c.text}};
}

inline void to_json(Json& j, const ImageContent& c)
{
    j = Json{{"type", c.type}, {"data", c.data}, {"mimeType", c.mimeType}};
}

inline void to_json(Json& j, const AudioContent& c)
{
    j = Json{{"type", c.type}, {"data", c.data}, {"mimeType", c.mimeType}};
}

} // namespace fastmcpp
