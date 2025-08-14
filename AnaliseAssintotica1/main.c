#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define MAX_VALOR 100000 

int contarParesForcaBruta(int arr[], int n, int k) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == k) {
                count++;
            }
        }
    }
    return count;
}

int comparar(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int contarParesComSorting(int arr[], int n, int k) {
    int* arr_copia = (int*)malloc(n * sizeof(int));
    if (arr_copia == NULL) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        arr_copia[i] = arr[i];
    }
    
    qsort(arr_copia, n, sizeof(int), comparar);
    
    int count = 0;
    int esquerda = 0;
    int direita = n - 1;

    while (esquerda < direita) {
        if (arr_copia[esquerda] + arr_copia[direita] == k) {
            count++;
            esquerda++;
            direita--;
        } else if (arr_copia[esquerda] + arr_copia[direita] < k) {
            esquerda++;
        } else {
            direita--;
        }
    }
    
    free(arr_copia);
    return count;
}

int contarParesComHash(int arr[], int n, int k) {
    int* hash_map = (int*)calloc(MAX_VALOR, sizeof(int));
    if (hash_map == NULL) {
        return -1;
    }
    
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] < MAX_VALOR) {
            hash_map[arr[i]]++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        int complemento = k - arr[i];
        
        if (complemento >= 0 && complemento < MAX_VALOR) {
            if (hash_map[complemento] > 0) {
                if (complemento == arr[i]) {
                    count += hash_map[complemento] - 1;
                } else {
                    count += hash_map[complemento];
                }
            }
        }
        hash_map[arr[i]] = 0; 
    }

    free(hash_map);
    return count / 2; 
}


int main() {
    int arr[] = {1, 5, 7, -1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 6;
    
    clock_t inicio, fim;
    double tempo_gasto;

    printf("Array de entrada: {1, 5, 7, -1, 5}\n");
    printf("Soma alvo (k): %d\n\n", k);

    inicio = clock();
    int resultado1 = contarParesForcaBruta(arr, n, k);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Solucao 1 (Forca Bruta - O(n^2)): %d pares encontrados\n", resultado1);
    printf("Tempo de execucao: %f segundos\n\n", tempo_gasto);
    
    inicio = clock();
    int resultado2 = contarParesComSorting(arr, n, k);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Solucao 2 (Ordenacao e Dois Ponteiros - O(n log n)): %d pares encontrados\n", resultado2);
    printf("Tempo de execucao: %f segundos\n\n", tempo_gasto);

    inicio = clock();
    int resultado3 = contarParesComHash(arr, n, k);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Solucao 3 (Tabela Hash - O(n)): %d pares encontrados\n", resultado3);
    printf("Tempo de execucao: %f segundos\n\n", tempo_gasto);

    return 0;
}