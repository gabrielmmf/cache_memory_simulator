# TP3-OC1

## Objetivos do trabalho

Desenvolver simulador e cache de um nível

Entrada => acessos de memória

Saída => Qual linha o bloco de memória RAM será armazenado

OBS: Desenvolver política de substituição de páginas

## Especificação do Simulador

Nome do arquivo => simulador

Argumentos:

1. Tamanho da cache (4096 = 4KB)

2. Tamanho de cada linha (1024 = 1KB)

3. Tamanho de cada grupo (2 = 2-way associativo)

4. Nome do arquivo com os acessos à memória

Parâmetros fixos:

1. Endereçamento de 32 bits

2. Endereços referenciam bytes

3. Politica de substituição LRU

4. Alocação de linhas

Dicas:

1. Utilizar tipo uint32_t da biblioteca <sys/types.h>

2. Implementar LRU com timestamp

## Planejamento

1. Implementar uma Estrutura de Dados representando uma memória

2. Inicializar a memória com os parâmetros cache_size, line_size, group_size

3. Criar função access que recebe um endereço e realiza a simulação de seu acesso:

   1. Calcula deslocamento, tag e identificador

   2. Utiliza a tag para acessar um grupo

      1. Se o identificador está no grupo: Move para o último lugar da lista de leastRecentlyUsed

      2. Senão:

         1. Se o grupo está cheio:

            1. Encontra o primeiro da lista de leastRecentlyUsed nos grupos
            2. Substitui ele
            3. Remove o primeiro da lista de leastRecentlyUsed

         2. Senão: Insere o identificador no final do grupo

         3. Insere o identificador no final da lista de leastRecentlyUsed
