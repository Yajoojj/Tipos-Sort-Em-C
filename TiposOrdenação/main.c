#include <stdio.h>
#include <stdlib.h>

// ==================== FUNÇÃO PARA IMPRIMIR O ARRAY ====================
// Percorre o array e imprime seus elementos na tela
void print(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// ==================== BUBBLE SORT ====================
// Percorre o array várias vezes e troca elementos adjacentes fora de ordem.
// Se nenhuma troca for feita em uma passagem, o array já está ordenado.
void bubble(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0; // Flag para verificar se houve troca
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // Se está fora de ordem, troca os elementos
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break; // Se não houve trocas, o array já está ordenado
    }
}

// ==================== INSERTION SORT ====================
// Insere cada elemento na posição correta dentro da parte ordenada do array.
void insertionSort(int arr[], int n) {
    for (int i = 1, j; i < n; i++) {
        int key = arr[i]; // Elemento a ser inserido na posição correta
        for (j = i - 1; j >= 0 && arr[j] > key; j--) {
            arr[j + 1] = arr[j]; // Move os elementos para abrir espaço
        }
        arr[j + 1] = key; // Insere o elemento na posição correta
        print(arr, n); // Exibe o array a cada iteração (opcional)
    }
}

// ==================== SELECTION SORT ====================
// Encontra o menor elemento da parte não ordenada e o coloca na posição correta.
void selection(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i; // Assume que o menor elemento está na posição atual
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min])
                min = j; // Atualiza o índice do menor elemento encontrado

        // Troca o menor elemento encontrado com o primeiro elemento da parte não ordenada
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

// ==================== MERGE SORT ====================
// Função para intercalar dois subarrays ordenados em um único array ordenado
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    if (!L || !R) { // Verifica se a alocação foi bem-sucedida
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i]; // Copia os elementos do primeiro subarray
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j]; // Copia os elementos do segundo subarray

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

// Função principal do Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; // Encontra o meio do array
        mergeSort(arr, l, m); // Ordena a primeira metade
        mergeSort(arr, m + 1, r); // Ordena a segunda metade
        merge(arr, l, m, r); // Junta as metades ordenadas
    }
}

// ==================== QUICK SORT ====================
// Particiona o array escolhendo um pivô e reorganizando os elementos
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Escolhe o último elemento como pivô
    int i = low;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) { // Se o elemento é menor que o pivô, troca de lugar
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    // Coloca o pivô na posição correta
    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;

    return i; // Retorna a posição do pivô
}

// Função principal do Quick Sort
void quick(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Particiona o array
        quick(arr, low, pi - 1); // Ordena a parte antes do pivô
        quick(arr, pi + 1, high); // Ordena a parte depois do pivô
    }
}

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    int original[] = {5, 3, 8, 4, 2, 7, 1, 10}; // Array original
    int n = sizeof(original) / sizeof(original[0]); // Determina o tamanho do array

    // Ponteiros para as funções de ordenação
    void (*sorts[])(int[], int) = {bubble, insertionSort, selection};
    void (*sorts3[])(int[], int, int) = {mergeSort, quick};

    // Nomes das ordenações para exibição
    char *nomes[] = {"Bubble", "Insertion", "Selection", "Merge", "Quick"};

    // Testa cada algoritmo de ordenação
    for (int i = 0; i < 5; i++) {
        int arr[n]; // Cria um array auxiliar para não modificar o original
        for (int j = 0; j < n; j++)
            arr[j] = original[j]; // Copia os elementos do array original

        // Chama a função de ordenação correspondente
        if (i < 3)
            sorts[i](arr, n);
        else
            sorts3[i - 3](arr, 0, n - 1);

        printf("%s Sort: ", nomes[i]); // Exibe o nome do algoritmo
        print(arr, n); // Exibe o array ordenado
    }

    return 0;
}
