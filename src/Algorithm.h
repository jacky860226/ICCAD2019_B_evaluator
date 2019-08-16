#pragma once
#include <cctype>
#include <string>
#include <algorithm>

#include "type.h"

bool isUnsignedNumber(const std::string &s)
{
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}