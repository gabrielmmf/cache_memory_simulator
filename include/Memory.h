#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#ifndef MEMORY_H
#define MEMORY_H

#define ADDRESSING 32

using namespace std;

class Memory
{
public:
    Memory(unsigned _cache_size, unsigned _line_size, unsigned _group_size);

    virtual ~Memory();

    void print();

    void access(uint32_t address);

private:
    unsigned calcOffset(unsigned line_size);
    unsigned calcTag(unsigned n_lines, unsigned group_size);

    unsigned cache_size;
    unsigned line_size;
    unsigned group_size;
    unsigned n_lines;
    unsigned n_groups;
    unsigned n_bits_offset;
    unsigned n_bits_tag;
    unsigned n_bits_id;

    vector<vector<unsigned>> leastRecentlyUsed;
    vector<vector<unsigned>> groups;
};

#endif