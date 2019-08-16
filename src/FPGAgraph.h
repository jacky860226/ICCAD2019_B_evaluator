#pragma once
#include <cstddef>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>

#include "undo_disjoint_set.h"
#include "errorMessageString.h"

using std::getline;
using std::pair;
using std::string;
using std::vector;

struct FPGAgraph
{
    size_t Vertex_num, Edge_num, Net_num, Group_num;
    vector<pair<size_t, size_t>> edge;
    vector<vector<size_t>> net;
    vector<vector<size_t>> group;

    string read(const string &filepath)
    {
        std::ifstream fin(filepath);
        if (!fin.is_open())
            return err::file_not_open;
        if (!(fin >> Vertex_num))
            return err::syntax_error;
        if (!(fin >> Edge_num))
            return err::syntax_error;
        if (!(fin >> Net_num))
            return err::syntax_error;
        if (!(fin >> Group_num))
            return err::syntax_error;

        if (Vertex_num < 1 || Vertex_num > 500)
            return err::out_of_range;
        if (Edge_num > Vertex_num * (Vertex_num - 1) / 2)
            return err::out_of_range;
        if (Net_num < 1 || Net_num > 1000000)
            return err::out_of_range;
        if (Group_num < 1 || Group_num > 1000000)
            return err::out_of_range;

        DisjointSet DST;
        DST.init(Vertex_num);

        edge.resize(Edge_num);
        for (auto &e : edge)
        {
            if (!(fin >> e.first >> e.second))
                return err::syntax_error;
            if (e.first >= Vertex_num || e.second >= Vertex_num)
                return err::out_of_range;
            DST.combine(e.first, e.second);
        }
        if (DST.size(0) < Vertex_num)
            return err::FPGA_not_connect;

        string buff;
        getline(fin, buff);

        net.resize(Net_num);
        for (auto &n : net)
        {
            getline(fin, buff);
            std::stringstream ss(buff);
            size_t tmp;
            for (; !ss.eof();)
            {
                ss >> tmp;
                if (ss.fail())
                    return err::syntax_error;
                if (tmp >= Vertex_num)
                    return err::out_of_range;
                n.emplace_back(tmp);
            }
            if (n.empty())
                return err::syntax_error;
        }

        group.resize(Group_num);
        for (auto &g : group)
        {
            getline(fin, buff);
            std::stringstream ss(buff);
            size_t tmp;
            for (; !ss.eof();)
            {
                ss >> tmp;
                if (ss.fail())
                    return err::syntax_error;
                if (tmp >= Net_num)
                    return err::out_of_range;
                g.emplace_back(tmp);
            }
            if (g.empty())
                return err::syntax_error;
        }
        return "";
    }
};