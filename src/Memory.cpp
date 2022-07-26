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

void Memory::print()
{
    cout << "================" << endl
         << "IDX V ** ADDR **" << endl;
    unsigned index = 0;
    for (unsigned i = 0; i < n_groups; i++)
    {
        for (unsigned j = 0; j < group_size; j++)
        {
            std::cout << std::setfill('0') << std::setw(3) << dec << index << " ";
            if (j < groups[i].size())
                cout << "1 "
                     << "0x" << setfill('0') << setw(8) << right << uppercase << hex << groups[i][j] << endl;
            else
                cout << "0" << endl;
            index++;
        }
    }
}

void Memory::access(uint32_t address)
{
    // Obtendo offset, tag e id
    unsigned offset = 0;
    unsigned tag = 0;
    unsigned id = 0;

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
    // Lógica para fazer um acesso à memória
    std::vector<unsigned>::iterator itr = std::find(leastRecentlyUsed[tag].begin(), leastRecentlyUsed[tag].end(), id);

    unsigned index = 0;

    // O arquivo está no grupo
    // Move o arquivo para a última posição do leastRecentlyUsed
    if (itr != leastRecentlyUsed[tag].cend())
    {
        index = std::distance(leastRecentlyUsed[tag].begin(), itr);
        leastRecentlyUsed[tag].erase(leastRecentlyUsed[tag].begin() + index);
        leastRecentlyUsed[tag].push_back(id);
    }
    // O arquivo não está no grupo
    // Caso o grupo esteja cheio, apaga o primeiro item do least recently used
    else
    {
        // Se o grupo está cheio:
        if (leastRecentlyUsed[tag].size() >= group_size)
        {
            /*
            1. Encontra o primeiro da lista de leastRecentlyUsed nos grupos
            2. Substitui ele no grupo
            3. Remove o primeiro da lista de leastRecentlyUsed
             */
            itr = std::find(groups[tag].begin(), groups[tag].end(), leastRecentlyUsed[tag][0]);
            index = std::distance(groups[tag].begin(), itr);
            groups[tag][index] = id;
            leastRecentlyUsed[tag].erase(leastRecentlyUsed[tag].begin());
        }
        else
        {
            // Se o grupo não está cheio: Insere o identificador no final do grupo
            groups[tag].push_back(id);
        }
        // Em qualquer caso, o leastRecentlyUsed é alterado
        leastRecentlyUsed[tag].push_back(id);
    }
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
    n_bits_id = ADDRESSING - n_bits_tag - n_bits_offset;

    groups.resize(n_groups);
    leastRecentlyUsed.resize(n_groups);
}

Memory::~Memory()
{
}