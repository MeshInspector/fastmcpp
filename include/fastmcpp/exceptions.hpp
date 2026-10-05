#pragma once
#include "fastmcpp/export.hpp"
#include <stdexcept>
#include <string>

namespace fastmcpp
{

struct FASTMCPP_CLASS Error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

struct FASTMCPP_CLASS NotFoundError : public Error
{
    using Error::Error;
};

struct FASTMCPP_CLASS ValidationError : public Error
{
    using Error::Error;
};

struct FASTMCPP_CLASS ToolTimeoutError : public Error
{
    using Error::Error;
};

struct FASTMCPP_CLASS TransportError : public Error
{
    using Error::Error;
};

} // namespace fastmcpp
