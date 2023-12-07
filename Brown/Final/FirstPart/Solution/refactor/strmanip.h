#pragma once

#include <string_view>

int ConvertToInt(string_view str);

std::string_view ReadToken(std::string_view& s, std::string_view delimiter = " ");

