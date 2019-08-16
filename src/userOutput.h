#pragma once
#include <vector>
#include <string>
#include <utility>

#include "type.h"
#include "Algorithm.h"
#include "FPGAgraph.h"
#include "errorMessageString.h"

using std::string;
using std::vector;
struct userOutput
{
    vector<vector<std::pair<size_t, unsigned long long>>> routeNet;
    string read(const string &filepath, const FPGAgraph &G)
    {
        std::ifstream fin(filepath);
        if (!fin.is_open())
            return err::file_not_open;

        routeNet.resize(G.Net_num);
        size_t nid = 0;
        for (auto &n : routeNet)
        {
            size_t num;
            if (!(fin >> num))
                return err::syntax_error;
            while (num--)
            {
                size_t eid;
                string buff;
                if (!(fin >> eid >> buff))
                    return err::syntax_error;
                if (!isUnsignedNumber(buff))
                    return err::syntax_error;
                bigN tdm_ratio(buff);
                if (tdm_ratio <= bigN(0))
                    return err::syntax_error;
                if (eid >= G.Edge_num)
                    return err::out_of_range;
                if (tdm_ratio % bigN(2) != bigN(0))
                    return err::TDM_ratio_not2 + "(at Net id = " + std::to_string(nid) + ")";
                if (tdm_ratio > bigN(4294967296))
                    return "TDM ratio: "+err::out_of_range;
                n.emplace_back(eid, tdm_ratio);
            }
            ++nid;
        }
        return "";
    }
};