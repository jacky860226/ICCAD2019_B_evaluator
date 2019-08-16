#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "type.h"
#include "FPGAgraph.h"
#include "userOutput.h"
#include "undo_disjoint_set.h"

using std::map;
using std::string;
using std::vector;
struct checker
{
    bigN ans;
    LDB MAXLDB;
    vector<map<unsigned long long,size_t>> ratio;
    vector<bigN> netCost, groupCost;
    string check(const FPGAgraph &fg, const userOutput &uo)
    {
        ans = 0;
        DisjointSet DST;
        DST.init(fg.Vertex_num);
        ratio.resize(fg.Edge_num);
        netCost.resize(fg.Net_num, bigN(0));
        groupCost.resize(fg.Group_num, bigN(0));
        size_t nid = 0;
        for (const auto &n : uo.routeNet)
        {
            DST.save();
            for (const auto &ed : n)
            {
                size_t eid = ed.first;
                ++ratio[eid][ed.second];
                netCost[nid] = netCost[nid] + bigN(ed.second);
                DST.combine(fg.edge[eid].first, fg.edge[eid].second);
            }
            size_t root = DST.find(fg.net[nid][0]);
            for (auto fgn : fg.net[nid])
            {
                if (DST.find(fgn) != root)
                    return "Net id = " + std::to_string(nid) + " not connect.";
            }
            DST.undo();
            ++nid;
        }
        MAXLDB = 0;
        for (size_t eid = 0; eid < ratio.size(); ++eid)
        {
            LDB add = LDB(0);
            for(auto m: ratio[eid]){
                add += LDB(m.second) / m.first;
            }
            if (add > LDB(1))
                return "Connection id = " + std::to_string(eid) + " TDM ratio > 1";
            MAXLDB = std::max(MAXLDB, add);
        }
        for (size_t i = 0; i < fg.Group_num; ++i)
        {
            for (auto n : fg.group[i])
            {
                groupCost[i] = groupCost[i] + netCost[n];
            }
        }
        ans = *std::max_element(groupCost.begin(), groupCost.end());
        return "";
    }
};