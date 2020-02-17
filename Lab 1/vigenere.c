#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAVE "TESTE"

#define INI 65
#define FIM 90
#define TAM_ALFABETO FIM - INI + 1

// 65 A ; 90 Z
// 32 ' ' ; 122 z

int size(char* vec) {
    return sizeof(vec)/sizeof(vec[0]);
}

char* cifraVigenere(char* textoClaro, char* chave) {
    char* textoCifrado = malloc(sizeof(textoClaro));
    for(int i = 0 ; i < strlen(textoClaro) ; i++) {
        textoCifrado[i] = ((textoClaro[i] + chave[i%strlen(chave)]) % TAM_ALFABETO) + INI;
    }
    return textoCifrado;
}

char* decifraVigenere(char* textoCifrado, char* chave) {
    char* textoClaro = malloc(sizeof(textoCifrado));
    int teste;
    for (int i = 0 ; i < strlen(textoCifrado) ; i++) {
        //textoClaro[i] = ((textoCifrado[i] - chave[i%strlen(chave)] + TAM_ALFABETO) % TAM_ALFABETO) + INI;
        teste = ((textoCifrado[i] - chave[i%strlen(chave)] + TAM_ALFABETO) % TAM_ALFABETO) + INI;
        textoClaro[i] = teste;
        printf("%d\n", teste);
    }

    return textoClaro;
}

int main(int argc, char **argv) {
    FILE *fptr;
    char c[1000];
    if ((fptr = fopen("vig.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    
    fgets(c, 1000, fptr);
    fclose(fptr);

    char* textoClaro = c;


    if(argc < 2) {
        printf("Use a flag C - Cifrar e D - decifrar\n");
        return 0;
    }
    if(strcmp("D", argv[1]) == 0) printf("%s\n", decifraVigenere(textoClaro, CHAVE));
    else if(strcmp("C", argv[1]) == 0 && size(textoClaro) > 1) printf("%s\n", cifraVigenere(textoClaro, CHAVE));
    else printf("Coloque o texto no arquivo\n");
    
    return 0;
}
