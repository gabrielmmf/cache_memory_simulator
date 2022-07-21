#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <stdio.h>

#define ADDRESSING 32

using namespace std;

unsigned calcOffset(unsigned _line_size)
{
    unsigned bits = 0;
    while (_line_size != 1)
    {
        _line_size = _line_size / 2;
        bits++;
    }
    return bits;
}

unsigned calcTag(unsigned _n_lines, unsigned _group_size)
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

void printAddress(uint32_t address, unsigned n_bits_offset, unsigned n_bits_tag, string file_name)
{
    ofstream file(file_name, ofstream::app);
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

    file << tag << " "
         << "0x" << setfill('0') << setw(8) << right << uppercase << hex << id << endl;

    file.close();
}

int main(int argc, char *argv[])
{
    /*
    Lendo os argumentos para definir tamanho da cache,
    linha, grupo e arquivo a ser acessado
    */
    unsigned cache_size = 0;
    unsigned line_size = 0;
    unsigned group_size = 0;
    string file_name = "";

    cache_size = stoi(argv[1]);
    line_size = stoi(argv[2]);
    group_size = stoi(argv[3]);
    file_name = argv[4];

    // Lendo arquivo e armazenando nos acessos à memória

    ofstream file(file_name);
    uint32_t random_address;
    vector<uint32_t> addresses;
    srand(time(NULL));

    unsigned n_lines = cache_size / line_size;
    unsigned n_bits_offset = calcOffset(line_size);
    unsigned n_bits_tag = calcTag(n_lines, group_size);
    unsigned n_bits_id = ADDRESSING - n_bits_tag - n_bits_offset;

    ofstream delete_content(file_name + "_fields", std::ofstream::out | std::ofstream::trunc);
    delete_content.close();
    for (int i = 0; i < 16; i++)
    {
        random_address = 0;
        for (int j = 0; j < 32; j++)
        {
            random_address = random_address << 1;
            random_address = random_address | (rand() % 2);
        }

        addresses.push_back(random_address);
        printAddress(random_address, n_bits_offset, n_bits_tag, file_name + "_fields");
        file << "0x" << setfill('0') << setw(8) << right << uppercase << hex << random_address << endl;

        if (rand() % 2)
        {
            unsigned random = rand() % addresses.size();
            random_address = addresses[random];
            printAddress(random_address, n_bits_offset, n_bits_tag, file_name + "_fields");
            file << "0x" << setfill('0') << setw(8) << right << uppercase << hex << random_address << endl;
        }
    }
    file.close();
    return 0;
}
