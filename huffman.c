#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

// Nodo para árbol de Huffman
typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left, *right;
} HuffmanNode;

// MinHeap para árbol
typedef struct {
    int size;
    HuffmanNode* array[MAX_CHAR];
} MinHeap;

char* codes[MAX_CHAR]; // Arreglo para guardar códigos Huffman
int original_bits = 0;
int compressed_bits = 0;

// Función para crear nodo
HuffmanNode* createNode(char character, int frequency) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// Funciones MinHeap
void swap(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* heap, int i) {
    int smallest = i, l = 2*i + 1, r = 2*i + 2;
    if (l < heap->size && heap->array[l]->frequency < heap->array[smallest]->frequency)
        smallest = l;
    if (r < heap->size && heap->array[r]->frequency < heap->array[smallest]->frequency)
        smallest = r;
    if (smallest != i) {
        swap(&heap->array[i], &heap->array[smallest]);
        minHeapify(heap, smallest);
    }
}

HuffmanNode* extractMin(MinHeap* heap) {
    HuffmanNode* temp = heap->array[0];
    heap->array[0] = heap->array[--heap->size];
    minHeapify(heap, 0);
    return temp;
}

void insertMinHeap(MinHeap* heap, HuffmanNode* node) {
    int i = heap->size++;
    while (i && node->frequency < heap->array[(i-1)/2]->frequency) {
        heap->array[i] = heap->array[(i-1)/2];
        i = (i-1)/2;
    }
    heap->array[i] = node;
}

// Crear heap con nodos de frecuencia
MinHeap* createAndBuildMinHeap(int freq[]) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i]) {
            heap->array[heap->size++] = createNode(i, freq[i]);
        }
    }
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        minHeapify(heap, i);
    }
    return heap;
}

// Construcción del árbol de Huffman
HuffmanNode* buildHuffmanTree(int freq[]) {
    MinHeap* heap = createAndBuildMinHeap(freq);
    while (heap->size != 1) {
        HuffmanNode *left = extractMin(heap);
        HuffmanNode *right = extractMin(heap);
        HuffmanNode *top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertMinHeap(heap, top);
    }
    return extractMin(heap);
}

// Asignación de códigos
void assignCodes(HuffmanNode* root, char* code, int top) {
    if (root->left) {
        code[top] = '0';
        assignCodes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = '1';
        assignCodes(root->right, code, top + 1);
    }
    if (!root->left && !root->right) {
        code[top] = '\0';
        codes[(unsigned char)root->character] = strdup(code);
    }
}

// Codificar archivo
void encodeFile(const char* input, const char* output) {
    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        original_bits += 8;
        if (codes[ch]) {
            fputs(codes[ch], out);
            compressed_bits += strlen(codes[ch]);
        }
    }
    fclose(in);
    fclose(out);
}

// Decodificar archivo
void decodeFile(const char* encodedFile, HuffmanNode* root) {
    FILE* in = fopen(encodedFile, "r");
    printf("\n[Decodificado]: ");
    HuffmanNode* current = root;
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (ch == '0') current = current->left;
        else if (ch == '1') current = current->right;
        if (!current->left && !current->right) {
            putchar(current->character);
            current = root;
        }
    }
    printf("\n");
    fclose(in);
}

int main() {
    FILE *file = fopen("entrada.txt", "r");
    if (!file) {
        printf("No se pudo abrir entrada.txt\n");
        return 1;
    }

    int freq[MAX_CHAR] = {0};
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        freq[ch]++;
    }
    fclose(file);

    HuffmanNode* root = buildHuffmanTree(freq);
    char code[100];
    assignCodes(root, code, 0);

    encodeFile("entrada.txt", "codificado.txt");

    printf("Bits originales: %d\n", original_bits);
    printf("Bits comprimidos: %d\n", compressed_bits);
    printf("Tasa de compresión: %.2f%%\n", 100.0 * compressed_bits / original_bits);

    decodeFile("codificado.txt", root);

    return 0;
}
