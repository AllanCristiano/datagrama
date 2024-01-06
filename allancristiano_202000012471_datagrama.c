#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int ordem;
    int qtd;
    char **elementos;
} Linha;

void ajustarHeap(char **arr, int n, int i)
{
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && strcmp(arr[esquerda], arr[maior]) > 0)
        maior = esquerda;

    if (direita < n && strcmp(arr[direita], arr[maior]) > 0)
        maior = direita;

    if (maior != i)
    {
        char *temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;

        ajustarHeap(arr, n, maior);
    }
}

void heapSort(char **arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        ajustarHeap(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        char *temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        ajustarHeap(arr, i, 0);
    }
}

int main(int argc, char *argv[])
{

    (void)argc;
    FILE *arquivo = fopen(argv[1], "r");

    int totalLinhas, linhasPorVez;
    fscanf(arquivo, "%d %d", &totalLinhas, &linhasPorVez);

    Linha *linhas = malloc(totalLinhas * sizeof(Linha));
    Linha *buffer = NULL;
    size_t tamanhoRealBuffer = 0;

    for (int i = 0; i < totalLinhas; i++)
    {
        fscanf(arquivo, "%d %d", &linhas[i].ordem, &linhas[i].qtd);
        linhas[i].elementos = malloc(linhas[i].qtd * sizeof(char *));
        for (int j = 0; j < linhas[i].qtd; j++)
        {
            linhas[i].elementos[j] = malloc(3 * sizeof(char));
            fscanf(arquivo, "%s", linhas[i].elementos[j]);
        }
    }

    int od = 0;
    for (int i = 0; i < totalLinhas; i += linhasPorVez)
    {
        char **aux = NULL;
        size_t tamanhoAuxiliar = 0;
        printf("%d:", od++);

        // Loop para percorrer o buffer e adicionar elementos ao aux
        for (size_t b = 0; b < tamanhoRealBuffer; b++)
        {
            if (buffer[b].ordem < (i + linhasPorVez))
            {
                for (int x = 0; x < buffer[b].qtd; x++)
                {
                    aux = realloc(aux, (tamanhoAuxiliar + 1) * sizeof(char *));
                    aux[tamanhoAuxiliar++] = buffer[b].elementos[x];
                }
            }
        }

        // loop principal
        for (int j = i; j < (i + linhasPorVez) && j < totalLinhas; j++)
        {
            if (linhas[j].ordem < (i + linhasPorVez))
            {
                aux = realloc(aux, (tamanhoAuxiliar + linhas[j].qtd) * sizeof(char *));
                for (int x = 0; x < linhas[j].qtd; x++)
                {
                    aux[tamanhoAuxiliar++] = linhas[j].elementos[x];
                }
            }
            else
            {
                // Adiciona a linha ao buffer
                buffer = realloc(buffer, (tamanhoRealBuffer + 1) * sizeof(Linha));
                buffer[tamanhoRealBuffer++] = linhas[j];
            }
        }

        heapSort(aux, tamanhoAuxiliar);

        for (size_t k = 0; k < tamanhoAuxiliar; k++)
        {
            printf(" %s ", aux[k]);
        }
        printf("\n");
        free(aux);
    }

    // Libera memória
    for (int i = 0; i < totalLinhas; i++)
    {
        for (int j = 0; j < linhas[i].qtd; j++)
        {
            free(linhas[i].elementos[j]);
        }
        free(linhas[i].elementos);
    }
    free(linhas);
    free(buffer);

    return 0;
}
