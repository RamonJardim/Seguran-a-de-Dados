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

char* vigenereDecipher(char* cipherText, char* key) {
    int temp;
    char* clearText = malloc(sizeof(cipherText));
    for (int i = 0 ; i < strlen(cipherText) ; i++) {
      temp = (cipherText[i] - key[i%strlen(key)] + ALP_SIZE);
      temp %= ALP_SIZE;
      temp+=START;

      clearText[i] = temp;
    }

    return clearText;
}

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

int getCharFreq(char* text, char chr) {
    int result = 0;
    for(int i = 0 ; i < strlen(text) ; i++) {
        if(text[i] == chr) result++;
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

// Usadas para debug

// void printVec(char* vec) {
//     for(int i = 0 ; i < strlen(vec) ; i++) {
//         printf("%c ", vec[i]);
//     }
//     printf("\n");
// }

// void printVecInt(int* vec, int size) {
//     for(int i = 0 ; i < size ; i++) {
//         printf("%d ", vec[i]);
//     }
//     printf("\n");
// }

char* decipher(char* text, int keySize, char mostCommomChar) {
    char* key = malloc(keySize*sizeof(char));
    
    char dividedText[keySize][strlen(text)];
    int* mostCommomCharFreq[keySize];

    for(int i = 0 ; i < keySize ; i++) {
        mostCommomCharFreq[i] = (int*)malloc(256*sizeof(int));
        for(int j = 0 ; j < 256 ; j++)
            mostCommomCharFreq[i][j] = 0;
    }


    for(int j = 0 ; j < keySize ;j++){
        for(int i = 0 ; i < strlen(text) ; i++){
            dividedText[j][i] = text[i*keySize+j];
        }
    }

    for(int i = 0 ; i < keySize ; i++) {
        for(char k = START ; k < END ; k++) {
            mostCommomCharFreq[i][k] = getCharFreq(vigenereDecipher(dividedText[i], &k), mostCommomChar);
        }
    }

    for(int i = 0 ; i < keySize ; i++) {
        key[i] = getMaxIndex(mostCommomCharFreq[i], 256);
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
