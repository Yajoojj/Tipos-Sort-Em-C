#include <stdio.h>
#include <stdlib.h>

// Função para imprimir um array
void print(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);  // Imprime cada elemento do array
    printf("\n");  // Nova linha após imprimir todos os elementos
}

// ==================== BUBBLE SORT ====================
// Percorre repetidamente o array, trocando elementos adjacentes fora de ordem.
// Se nenhuma troca for feita em uma passagem, o array já está ordenado.
void bubble(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;  // Indica se houve troca na passagem atual
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {  // Se o elemento está fora de ordem, troca
                int temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
                swapped = 1;
            }
        if (!swapped) break;  // Se não houve troca, encerra o loop
    }
}

// ==================== INSERTION SORT ====================
// Insere cada elemento na posição correta dentro da parte já ordenada do array.
void insertionSort(int arr[], int n) {
    for (int i = 1, j; i < n; i++) {
        int key = arr[i];
        printf("O valor a ser inserido: %d\n",key);
        for (j = i - 1; j >= 0 && arr[j] > key; j--){
            printf("trocas realizadas: %d com %d \n",arr[j+1],arr[j]);
            arr[j + 1] = arr[j];
        }
        printf("Insere o valor %d no lugar correto que é a posicao %d \n",key,j+1);
        arr[j + 1] = key;
        imprime(arr,6);
    }
}
// ==================== SELECTION SORT ====================
// Encontra o menor elemento da parte não ordenada e o coloca na posição correta.
void selection(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;  // Assume que o menor elemento é o primeiro da parte não ordenada
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min]) min = j;  // Atualiza o índice do menor elemento encontrado
        int temp = arr[i]; arr[i] = arr[min]; arr[min] = temp;  // Troca os elementos
    }
}

// ==================== MERGE SORT ====================
// Algoritmo baseado no paradigma "Dividir para Conquistar".
// Divide o array em duas metades, ordena cada metade e depois intercala as duas partes ordenadas.
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int)), *R = malloc(n2 * sizeof(int));  // Arrays temporários

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];  // Copia a primeira metade
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];  // Copia a segunda metade

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];  // Intercala as metades
    while (i < n1) arr[k++] = L[i++];  // Copia os elementos restantes da primeira metade
    while (j < n2) arr[k++] = R[j++];  // Copia os elementos restantes da segunda metade

    free(L); free(R);  // Libera memória alocada
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;  // Encontra o meio do array
        mergeSort(arr, l, m);  // Ordena a primeira metade
        mergeSort(arr, m + 1, r);  // Ordena a segunda metade
        merge(arr, l, m, r);  // Junta as metades ordenadas
    }
}

// ==================== QUICK SORT ====================
// Escolhe um pivô e reorganiza os elementos para que os menores fiquem antes dele e os maiores depois.
// Depois, aplica recursivamente nas duas metades.
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low;  // Pivô é o último elemento
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot) {  // Se o elemento é menor que o pivô, troca de lugar
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            i++;
        }
    int temp = arr[i]; arr[i] = arr[high]; arr[high] = temp;  // Coloca o pivô na posição correta
    return i;  // Retorna a posição do pivô
}

void quick(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Particiona o array
        quick(arr, low, pi - 1);  // Ordena a parte antes do pivô
        quick(arr, pi + 1, high);  // Ordena a parte depois do pivô
    }
}

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    int original[] = {5, 3, 8, 4, 2, 7, 1, 10};  // Array original
    int n = sizeof(original) / sizeof(original[0]);  // Número de elementos do array

    // Ponteiros para as funções de ordenação
    void (*sorts[])(int[], int) = {bubble, insertion, selection};
    void (*sorts3[])(int[], int, int) = {mergeSort, quick};

    // Nomes das ordenações para exibição
    char *nomes[] = {"Bubble", "Insertion", "Selection", "Merge", "Quick"};

    // Testa cada algoritmo de ordenação
    for (int i = 0; i < 5; i++) {
        int arr[n];  // Cria um array auxiliar para não modificar o original
        for (int j = 0; j < n; j++) arr[j] = original[j];  // Copia os elementos do array original

        if (i < 3) sorts[i](arr, n);  // Para os três primeiros, chama a função com dois parâmetros
        else sorts3[i - 3](arr, 0, n - 1);  // Para MergeSort e QuickSort, chama com três parâmetros

        printf("%s Sort: ", nomes[i]);  // Exibe o nome do algoritmo
        print(arr, n);  // Exibe o array ordenado
    }

    return 0;
}
