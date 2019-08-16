// from Jinkela ACM-ICPC codebook
#pragma once
#include <cassert>
#include <vector>
#include <utility>
#include <algorithm>
using std::pair;
using std::vector;
struct DisjointSet
{
	// save() is like recursive
	// undo() is like return
	vector<size_t> fa, sz;
	vector<pair<size_t *, size_t>> h;
	vector<size_t> sp;
	void init(size_t n)
	{
		sz.resize(n);
		fa.resize(n);
		for (size_t i = 0; i < n; i++)
			sz[fa[i] = i] = 1;
		sp.clear();
		h.clear();
	}
	void assign(size_t *k, size_t v)
	{
		h.emplace_back(k, *k);
		*k = v;
	}
	void save()
	{
		sp.emplace_back(h.size());
	}
	void undo()
	{
		assert(!sp.empty());
		size_t last = sp.back();
		sp.pop_back();
		while (h.size() != last)
		{
			auto x = h.back();
			h.pop_back();
			*x.first = x.second;
		}
	}
	size_t find(size_t x)
	{
		while (fa[x] != x)
			x = fa[x];
		return x;
	}
	size_t size(size_t x){
		return sz[find(x)];
	}
	void combine(size_t x, size_t y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return;
		if (sz[x] < sz[y])
			std::swap(x, y);
		assign(&sz[x], sz[x] + sz[y]);
		assign(&fa[y], x);
	}
};