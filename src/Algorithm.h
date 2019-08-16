#pragma once
#include <cctype>
#include <string>
#include <algorithm>

#include "type.h"

bool isUnsignedNumber(const std::string &s)
{
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

std::string fracType_to_string(const fracType &data){
    std::string n = data.n;
    if(data.d == bigN(1)) return n;
    std::string d = data.d;
    return n + "/" + d;
}