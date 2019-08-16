#pragma once
#include <string>
using std::string;
namespace err
{
const string file_not_open = "Can not open FPGA file.";
const string syntax_error = "Syntax error.";
const string out_of_range = "Number out of range.";
const string FPGA_not_connect = "FPGA not connect.";
const string TDM_ratio_not2 = "TDM ratio is not multiple of 2.";
} // namespace err
