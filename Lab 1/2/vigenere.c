#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define KEY_SIZE 4
#define MOST_COMMOM_CHAR ' '

#define START 32
#define END 122
#define ALP_SIZE END - START + 1

// 65 A ; 90 Z
// 32 ' ' ; 122 z

char* readFile() {
  FILE *fptr;
  char* c = malloc(sizeof(char)*10000);
  if ((fptr = fopen("vig.txt", "r")) == NULL) {
      printf("Erro ao abrir o arquivo.");
      exit(1);
  }
   
  fgets(c, 10000, fptr);
  fclose(fptr);
  return c;
}

int* getCharFreq(char* text) {
    int* result = malloc(sizeof(int)*256);
    for(int i = 0 ; i < strlen(text) ; i++) {
        result[text[i]]++;
    }
    return result;
}

int getMaxIndex(int *vec, int size) {
    int maxIndex = -1;
    int maxValue = -INT_MAX;
    
    for(int i = 0 ; i < size ; i++) {
        if(vec[i] > maxValue) {
            maxIndex = i;
            maxValue = vec[i];
        }
    }

    return maxIndex;
}

char getMostFreqChar(char* text) {
    return (char)(getMaxIndex(getCharFreq(text), 256));
}

char* decipher(char* text, int keySize, char mostCommomChar) {
    char* key = malloc(keySize*sizeof(char));
    
    char* dividedText[keySize];

    for(int i = 0 ; i < keySize ;i++){
        dividedText[i] = (char*)malloc(strlen(text)*sizeof(char));
        for(int j = 0 ; j < strlen(text) ; j++){
            dividedText[i][j] = text[j*keySize+i];
        }
        key[i] = getMostFreqChar(dividedText[i]) - mostCommomChar + START;
    }
	
	key[keySize] = '\0';

    return key;
}

int main(int argc, char **argv) {
    char* text = readFile();

    char* key = decipher(text, KEY_SIZE, MOST_COMMOM_CHAR);
    printf("A chave é %s\n", key);
    return 0;
}
