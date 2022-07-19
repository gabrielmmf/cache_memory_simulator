#include "Memory.h"

using namespace std;

void print_binary(unsigned x)
{
    for (int i = sizeof(x) << 3; i; i--)
        putchar('0' + ((x >> (i - 1)) & 1));
}

void print_binary32(uint32_t x)
{
    for (int i = sizeof(x) << 3; i; i--)
        putchar('0' + ((x >> (i - 1)) & 1));
}

unsigned Memory::calcOffset(unsigned _line_size)
{
    unsigned bits = 0;
    while (_line_size != 1)
    {
        _line_size = _line_size / 2;
        bits++;
    }
    return bits;
}

unsigned Memory::calcTag(unsigned _n_lines, unsigned _group_size)
{
    unsigned bits = 0;
    unsigned groups = _n_lines / _group_size;

    while (groups != 1)
    {
        groups = groups / 2;
        bits++;
    }
    return bits;
}

void Memory::access(uint32_t address)
{
    // Obtendo offset, tag e id
    unsigned offset = 0;
    unsigned tag = 0;
    unsigned id = 0;

    print_binary32(address);
    printf("\n");

    unsigned i = 0;
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

    // Lógica para fazer um acesso à memória
    std::vector<unsigned>::iterator itr = std::find(groups[tag].begin(), groups[tag].end(), id);

    unsigned index = 0;
    // O arquivo está no grupo
    // Move o arquivo para a última posição
    if (itr != groups[tag].cend())
    {
        unsigned index = std::distance(groups[tag].begin(), itr);
        groups[tag].erase(groups[tag].begin() + index);
        groups[tag].push_back(id);
    }
    // O arquivo não está no grupo
    // Caso o grupo esteja cheio, apaga o primeiro item
    else
    {
        if (groups[tag].size() > group_size)
            groups[tag].erase(groups[tag].begin());
        groups[tag].push_back(id);
    }

    for (unsigned i = 0; i < groups[tag].size(); i++)
    {
        cout << groups[tag][i] << " ";
    }
    cout << endl;
}

Memory::Memory(unsigned _cache_size, unsigned _line_size, unsigned _group_size)
{
    cache_size = _cache_size;
    line_size = _line_size;
    group_size = _group_size;
    n_lines = _cache_size / _line_size;
    n_groups = n_lines / _group_size;
    n_bits_offset = calcOffset(_line_size);
    n_bits_tag = calcTag(n_lines, _group_size);

    for (unsigned i = 0; i < n_groups; i++)
    {
        groups.push_back({});
    }
}

Memory::~Memory()
{
}