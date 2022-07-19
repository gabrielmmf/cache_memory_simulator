#include "Memory.h"

using namespace std;

void print_binary(unsigned int x)
{
    for (int i = sizeof(x) << 3; i; i--)
        putchar('0' + ((x >> (i - 1)) & 1));
}

void print_binary32(uint32_t x)
{
    for (int i = sizeof(x) << 3; i; i--)
        putchar('0' + ((x >> (i - 1)) & 1));
}

unsigned int Memory::calcOffset(unsigned int _line_size)
{
    unsigned int bits = 0;
    while (_line_size != 1)
    {
        _line_size = _line_size / 2;
        bits++;
    }
    return bits;
}

unsigned int Memory::calcTag(unsigned int _n_lines, unsigned int _group_size)
{
    unsigned int bits = 0;
    unsigned int groups = _n_lines / _group_size;

    while (groups != 1)
    {
        groups = groups / 2;
        bits++;
    }
    return bits;
}

void Memory::access(uint32_t address)
{
    // Obtendo deslocamento (offset)
    unsigned int offset = 0;
    unsigned int tag = 0;
    unsigned int id = 0;

    print_binary32(address);
    printf("\n");

    unsigned int i = 0;
    while (i < ADDRESSING)
    {
        if (i < n_bits_offset)
        {
            if (address & 1)
            {
                offset = offset | (1 << i);
            }
        }
        else if (i < n_bits_offset + n_bits_tag)
        {
            if (address & 1)
            {
                tag = tag | (1 << (i - n_bits_offset));
            }
        }
        else
        {
            if (address & 1)
            {
                id = id | (1 << (i - n_bits_offset - n_bits_tag));
            }
        }
        address = address >> 1;
        i++;
    }

    printf("id: %d", id);
    printf("\n");
    printf("tag: %d", tag);
    printf("\n");
    printf("offset: %d", offset);
    printf("\n");
}

Memory::Memory(unsigned int _cache_size, unsigned int _line_size, unsigned int _group_size)
{
    cache_size = _cache_size;
    line_size = _line_size;
    group_size = _group_size;
    n_lines = _cache_size / _line_size;
    n_bits_offset = calcOffset(_line_size);
    n_bits_tag = calcTag(n_lines, _group_size);
}

Memory::~Memory()
{
}