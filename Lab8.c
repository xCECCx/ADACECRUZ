#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Estructura para caché (memoization)
typedef struct Node {
    char key[61];
    bool value;
    struct Node* next;
} Node;

#define HASH_SIZE 100003

Node* hashTable[HASH_SIZE];

unsigned int hash(const char* key) {
    unsigned int h = 0;
    while (*key) {
        h = (h * 31 + *key++) % HASH_SIZE;
    }
    return h;
}

bool get(const char* key, bool* found) {
    unsigned int h = hash(key);
    Node* node = hashTable[h];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            *found = true;
            return node->value;
        }
        node = node->next;
    }
    *found = false;
    return false;
}

void put(const char* key, bool value) {
    unsigned int h = hash(key);
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->key, key);
    node->value = value;
    node->next = hashTable[h];
    hashTable[h] = node;
}

bool isScramble(const char* s1, const char* s2) {
    int len = strlen(s1);
    if (strcmp(s1, s2) == 0) return true;
    if (len <= 1) return false;

    char key[61];
    snprintf(key, sizeof(key), "%s %s", s1, s2);
    bool found;
    bool cached = get(key, &found);
    if (found) return cached;

    // Verificación por frecuencia de letras
    int count[26] = {0};
    for (int i = 0; i < len; i++) {
        count[s1[i] - 'a']++;
        count[s2[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            put(key, false);
            return false;
        }
    }

    // División y recursión
    for (int i = 1; i < len; i++) {
        // Sin swap
        if (isScramble(strndup(s1, i), strndup(s2, i)) &&
            isScramble(s1 + i, s2 + i)) {
            put(key, true);
            return true;
        }
        // Con swap
        if (isScramble(strndup(s1, i), strndup(s2 + len - i, i)) &&
            isScramble(s1 + i, strndup(s2, len - i))) {
            put(key, true);
            return true;
        }
    }

    put(key, false);
    return false;
}

int main() {
    char s1[31], s2[31];
    printf("Ingresa s1: ");
    scanf("%30s", s1);
    printf("Ingresa s2: ");
    scanf("%30s", s2);

    if (strlen(s1) != strlen(s2)) {
        printf("false\n");
        return 0;
    }

    if (isScramble(s1, s2)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}
