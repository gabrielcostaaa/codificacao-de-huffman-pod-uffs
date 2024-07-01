# Codificação de Huffman para Compressão de Arquivos Texto - GEX609 - Pesquisa e Ordenação de Dados - 2024/1

Este sistema foi desenvolvido como parte da avaliação da disciplina de Pesquisa e Ordenação de Dados. O programa implementa a Codificação de Huffman para comprimir e descomprimir um texto lido de um arquivo.

## Descrição do Projeto

O programa realiza a leitura de uma string de entrada e apresenta a Codificação de Huffman para os diferentes caracteres da string. Todos os caracteres da string são em minúsculas e o caractere de espaço é incluído na Codificação. O texto base é lido de um arquivo chamado `amostra.txt`. Após a criação da árvore de Huffman, o texto é codificado em representação binária e gravado no arquivo `codificado.txt`. Este arquivo é então decodificado e o resultado é salvo em `decodificado.txt`.

## Requisitos

- O trabalho deve ser implementado em C.
- Não utilize bibliotecas de ordenação prontas da linguagem.
- Somente são permitidas as bibliotecas: `stdio.h`, `stdlib.h` e `string.h`.

## Funcionalidades Principais

```c
//Iniciação e Preenchimento da Tabela de Frequência
void iniciaTabela(unsigned int tab[]);
void preencheTabela(unsigned char frase[], unsigned int tab[]);

//Criação e Impressão da Lista Encadeada Ordenada
void criarLista(Lista *lista);
void inserirOrdenado(Lista *lista, Node *node);
void preencherLista(unsigned int tab[], Lista *lista);
void imprimeLista(Lista *lista);

//Montagem e Impressão da Árvore de Huffman
Node* montarArvore(Lista *lista);
void imprimeArvore(Node *raiz, int tam);

//Geração e Impressão do Dicionário de Huffman
char** alocaDicionario(int colunas);
void gerarDicionario(char **dicionario, Node *raiz, char *caminho, int colunas);
void imprimeDicionario(char **dicionario);

//Codificação e Decodificação
char* codificar(char **dicionario, unsigned char *texto);

