#include <iostream>

#ifndef MEMORY_H
#define MEMORY_H

#define ADDRESSING 32

using namespace std;

class Memory
{
public:
    Memory(unsigned int _cache_size, unsigned int _line_size, unsigned int _group_size);

    virtual ~Memory();

    void access(uint32_t address);

private:
    unsigned int calcOffset(unsigned int line_size);
    unsigned int calcTag(unsigned int n_lines, unsigned int group_size);

    unsigned int cache_size;
    unsigned int line_size;
    unsigned int group_size;
    unsigned int n_lines;
    unsigned int n_bits_offset;
    unsigned int n_bits_tag;
};

#endif