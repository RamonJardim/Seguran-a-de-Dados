#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY "AbC!"

#define START 32
#define END 122
#define ALP_SIZE END - START + 1
#define MOST_COMMOM_CHAR ' '

// 65 A ; 90 Z
// 32 ' ' ; 122 z

char* vigenereCipher(char* clearText, char* key) {
  int temp;
  char* cipherText = malloc(sizeof(clearText));
  for(int i = 0 ; i < strlen(clearText) ; i++) {
    temp = (clearText[i] + key[i%strlen(key)]);
    temp %= ALP_SIZE;
    temp += START;
    cipherText[i] = temp;
  }
  return cipherText;
}

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

void checks(char* text, int argc, char** argv) {
    if(argc < 2) {
        printf("Use o argumento 'C' para Cifrar e 'D' para decifrar\n");
        return;
    }
    if(strcmp("D", argv[1]) == 0)
        printf("%s\n", vigenereDecipher(text, argv[2] ? argv[2] : KEY));
    else if(strcmp("C", argv[1]) == 0 && strlen(text) > 1)
        printf("%s\n", vigenereCipher(text, KEY));
    else if(strlen(text) == 0)
        printf("Coloque o texto no arquivo vig.txt\n");
    else
        printf("Use a flag C - Cifrar e D - decifrar\n");
}

int main(int argc, char **argv) {
    char* text = readFile();
    
    checks(text, argc, argv);
    
    return 0;
}
