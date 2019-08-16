#include <iostream>

#include "FPGAgraph.h"
#include "userOutput.h"
#include "checker.h"

using std::cin;
using std::cout;
int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        cout << "evaluter need 2 argument!\n";
        return 0;
    }
    FPGAgraph fg;
    cout << "start read FPGA graph file\n";
    auto s = fg.read(argv[1]);
    if (s == "")
        cout << "read success!" << '\n';
    else
    {
        cout << "\tError! " << s << '\n';
        return 0;
    }
    userOutput uo;
    cout << "start read user output file\n";
    s = uo.read(argv[2], fg);
    if (s == "")
        cout << "read success!" << '\n';
    else
    {
        cout << "\tError! " << s << '\n';
        return 0;
    }
    checker chk;
    cout << "start check TDM ratio and net connection\n";
    s = chk.check(fg, uo);
    if (s == "")
    {
        cout << "\tNo error, maximum total TDM ratio of all net groups is: " << chk.ans << '\n';
    }
    else
    {
        cout << "\tError! " << s << '\n';
        return 0;
    }
    cout << "finish all check, program terminate.\n";
    return 0;
}
