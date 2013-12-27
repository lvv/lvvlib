// last_n - circular buffer class
// Part of lvvlib - https://github.com/lvv/lvvlib
// Copyright (c) 2000-2013
// Leonid Volnitsky (Leonid@Volnitsky.com)

			    #ifndef  LVV_LAST_N_H
			    #define  LVV_LAST_N_H

#include <cstddef>
template<class T, size_t N>
struct last_n {
	size_t oldest=0;
	T ring[N]={0};
	void push_back(T x)  { ring[oldest++] = x;   oldest %= N; };
	T prev(size_t i)     { return ring[(oldest-1-i+N)%N];};
};
			    #endif
