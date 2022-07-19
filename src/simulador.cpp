#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include "Memory.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*
    Lendo os argumentos para definir tamanho da cache,
    linha, grupo e arquivo a ser acessado
    */
    unsigned int cache_size = 0;
    unsigned int line_size = 0;
    unsigned int group_size = 0;
    string file_name = "";

    cache_size = stoi(argv[1]);
    line_size = stoi(argv[2]);
    group_size = stoi(argv[3]);
    file_name = argv[4];

    Memory mem(cache_size, line_size, group_size);
    /*
cout << mem.n_bits_deslocamento << endl
     << mem.n_bits_tag << endl; */

    // Lendo arquivo e armazenando nos acessos à memória

    FILE *file;
    file = fopen(file_name.c_str(), "r");
    uint32_t address;
    while (fscanf(file, "%x", &address) != EOF)
    {
        mem.access(address);
        printf("\n");
    }
    fclose(file);
    return 0;
}
