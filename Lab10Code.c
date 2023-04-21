#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    struct Trie *element[ALPHABET_SIZE];
    int count;
};

// Function to insert a word into the Trie
void insert(struct Trie **ppTrie, char *word) {
    if (*ppTrie == NULL) {
        *ppTrie = (struct Trie *) malloc(sizeof(struct Trie));
        memset((*ppTrie)->element, 0, sizeof((*ppTrie)->element));
        (*ppTrie)->count = 0;
    }

    struct Trie *current = *ppTrie;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (current->element[index] == NULL) {
            current->element[index] = (struct Trie *) malloc(sizeof(struct Trie));
            memset(current->element[index]->element, 0, sizeof(current->element[index]->element));
            current->element[index]->count = 0;
        }
        current = current->element[index];
    }
    current->count++;
}

// Function to count the number of occurrences of a word in the Trie
int numOccurrences(struct Trie *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    }

    struct Trie *current = pTrie;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (current->element[index] == NULL) {
            return 0;
        }
        current = current->element[index];
    }
    return current->count;
}

// Function to deallocate the Trie data structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pTrie->element[i] = deallocateTrie(pTrie->element[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    // Read the number of words in the dictionary
    int numWords;
    scanf("%d", &numWords);

    // Parse line by line, and insert each word to the trie data structure
    char word[100];
    struct Trie *trie = NULL;
    for (int i = 0; i < numWords; i++) {
        scanf("%s", word);
        insert(&trie, word);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("%s : %d\n", pWords[i], numOccurrences(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }

    return 0;
}
