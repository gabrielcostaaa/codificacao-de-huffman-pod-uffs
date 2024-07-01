#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 256

// ================ DEFINIÇÕES DAS STRUCTS ================

typedef struct node{
    unsigned char caracter;
    int frequencia;
    struct node *left, *right, *next;
}Node;

typedef struct{
    Node *first;
    int tam;
    
}Lista;

// ========================================================

// ================ DEFINIÇÕES DAS FUNÇÕES ================
void iniciaTabela(unsigned int tab[]) {
    int i;
    
    for(i = 0 ; i < TAM ; i++){
        tab[i] = 0;
    }
}

void preencheTabela(unsigned char frase[], unsigned int tab[]) {
    int i = 0;
    
    while(frase[i] != '\0'){
        tab[frase[i]]++;
        i++;
    }
}

void imprimeTabela(unsigned int tab[]){
    int i;
    
    printf("\n\tTabela de Frequência\n\n");
    for(i = 0 ; i < TAM ; i++){
        if(tab[i] > 0){
        printf("\tCaractere: %c = Frequência: %d = Código ASCII: %d\n", i, tab[i], i);
        }
    }
}

void criarLista(Lista *lista){
    lista->first = NULL;
    lista->tam = 0;
}

void inserirOrdenado(Lista *lista, Node *node) {
    
    Node *aux;
    
    if(lista->first == NULL){
        lista->first = node;
    } else if(node->frequencia < lista->first->frequencia){
        node->next = lista->first;
        lista->first = node;
    } else {
        aux = lista->first;
        while(aux->next != NULL && aux->next->frequencia <= node->frequencia){
            aux = aux->next;
        }
        node->next = aux->next;
        aux->next = node;
    }
    lista->tam++;
}

void preencherLista(unsigned int tab[], Lista *lista) {
    int i;
    Node *new;
    for(i = 0 ; i < TAM ; i++){
        if(tab[i] > 0){
            new = malloc(sizeof(Node));
            if(new){
                new->caracter = i;
                new->frequencia = tab[i];
                new->right = NULL;
                new->left = NULL;
                new->next = NULL;
                
                inserirOrdenado(lista, new);
            } else{
                printf("Erro na alocação de memória\n");
                break;
            }
        }
    }
}

void imprimeLista(Lista *lista) {
    Node *aux = lista->first;
    
    printf("\n\tLista Encadeada Ordenada de tamanho %d\n\n", lista->tam);
    while(aux){
        printf("\tCaracter: %c Frequência: %d\n", aux->caracter, aux->frequencia);
        aux = aux->next;
    }
}

Node* removeNoInicio(Lista *lista){
    Node *aux = NULL;
    
    if(lista->first){
        aux = lista->first;
        lista->first = aux->next;
        aux->next = NULL;
        lista->tam--;
    }
    
    return aux;
}

Node* montarArvore(Lista *lista){
    Node *primeiro, *segundo, *novo;
    
    
    while(lista->tam > 1){
        primeiro = removeNoInicio(lista);
        segundo = removeNoInicio(lista);
        novo = malloc(sizeof(Node));
        
        if(novo){
            novo->caracter = '+';
            novo->frequencia= primeiro->frequencia + segundo->frequencia;
            novo->left = primeiro;
            novo->right = segundo;
            novo->next = NULL;
            
            inserirOrdenado(lista, novo);
        } else{
            printf("Erro ao alocar memoria ao montar arvore");
            break;
        }
    }
    return lista->first;
}

void imprimeArvore(Node *raiz, int tam){
    if(raiz->left == NULL && raiz->right == NULL){
        printf("\nFolha: %c Altura: %d", raiz->caracter, tam);
    } else {
        imprimeArvore(raiz->left, tam + 1);
        imprimeArvore(raiz->right, tam + 1);
    }
}

int alturaArvore(Node *raiz){
    int left, right;
    
    if(raiz == NULL){
        return -1;    
    } else {
        left = alturaArvore(raiz->left) + 1;
        right = alturaArvore(raiz->right) + 1;
        
        if(left > right) {
            return left;
        } else{
            return right;
        }
    }
}

char** alocaDicionario(int colunas) {
    char **dicionario;
    int i;
    
    dicionario =malloc(sizeof(char*) * TAM);
    
    for(i = 0 ; i < TAM ; i++){
        dicionario[i] = calloc(colunas, sizeof(char));
    }
    
    return dicionario;
}

void gerarDicionario(char **dicionario, Node *raiz, char *caminho, int colunas){
    char esquerda[colunas], direita[colunas];
    
    if(raiz->left == NULL && raiz->right == NULL){
        strcpy(dicionario[raiz->caracter], caminho);
    } else {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);
        
        strcat(esquerda, "0");
        strcat(direita, "1");
        
        gerarDicionario(dicionario, raiz->left, esquerda, colunas);
        gerarDicionario(dicionario, raiz->right, direita, colunas);
    }
}

void imprimeDicionario(char **dicionario){
    int i;
    
    printf("\n\nDicionario:");
    for(i = 0 ; i < TAM ; i++){
        if(strlen(dicionario[i]) > 0){
            printf("\n%3d: %s", i, dicionario[i]);
        }
    }
}


int calculaTamanhoString(char **dicionario, char *texto){
    int i = 0, tam = 0;
    while(texto[i] != '\0'){
        tam = tam + strlen(dicionario[texto[i]]);
        i++;
    }
    return tam + 1;
}

char* codificar(char **dicionario, unsigned char *texto){
    
    int i = 0, tam = calculaTamanhoString(dicionario, texto);
    char *codigo = calloc(tam, sizeof(char));
    
    while(texto[i] != '\0'){
        strcat(codigo, dicionario[texto[i]]);
        i++;
    }
    return codigo;
}

// ========================================================


int main() {

    FILE *fp = fopen("amostra.txt", "rt");
    
    if (fp == NULL) {
     printf("Erro na abertura do arquivo!");
     exit(1);
    }
    
    unsigned char frase[100];
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    Node *arvore;
    int colunas;
    char **dicionario;
    char *codificado;
    
    while (fgets(frase, sizeof(frase), fp) != NULL) {
        printf("%s", frase);
    }

    iniciaTabela(tabela_frequencia);
    preencheTabela(frase, tabela_frequencia);
    imprimeTabela(tabela_frequencia);

    criarLista(&lista);
    preencherLista(tabela_frequencia, &lista);
    imprimeLista(&lista);
    
    arvore = montarArvore(&lista);
    printf("\n\nArvore de Huffman");
    imprimeArvore(arvore, 0);
    
    colunas = alturaArvore(arvore) + 1;
    dicionario =alocaDicionario(colunas);
    gerarDicionario(dicionario, arvore, "", colunas);
    imprimeDicionario(dicionario);
    
    codificado = codificar(dicionario, frase);
    printf("\n\nTexto codificado: %s", codificado);

    fclose(fp);
    
    FILE *fp2 = fopen("codificado.txt", "w");
    if (fp2 == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return 1;
    }

    
    fprintf(fp2, "%s", codificado);
    fclose(fp2);

    
    FILE *fp3 = fopen("codificado.txt", "r");
    if (fp3 == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return 1;
    }

    
    char buffer[TAM];
    while (fgets(buffer, sizeof(buffer), fp3) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp3);
    
    return 0;
}
