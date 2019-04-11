#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char palavra[47];
char forca[47];	
char erros[6];

void boneco(int contador);
int mostrarResultado(int resultado);
int jogo();

#if defined(__MINGW32__) || defined(_MSC_VER)//Separa os defines para Windows e Linux
#define limpar_input() fflush(stdin)
#define limpar_tela() system("cls")
#else
#define limpar_input() __fpurge(stdin)
#define limpar_tela() system("clear")
#endif

void limparBuffer(char *buf, int tamanho) {//Limpar o buffer
    int j = 0;
    for (j = 0; j < tamanho; j++) {
        buf[j] = 0;
    }
}
void trimEnd(char *str) { //Tira o \n que o fgets lê junto com a variavel pra ir para a ultima linha
    int p;
    for (p = strlen(str); isspace(str[p]); p--) {
        str[p] = 0;
    }
}

int ehLetra(char c) {//Indica que letras maiusculas e minusculas são letras
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char maiuscula(char c) {
    return (c >= 'a' && c <= 'z') ? (c - 32) : c;
}
void start(void) {//Função que dá inicio ao jogo
	limpar_tela();
	
	//palavra// = (char)malloc(47*sizeof(char));
	//forca = (char*)malloc(47*sizeof(char));

	
	limparBuffer(palavra, 47);
    limparBuffer(forca, 47);
    limparBuffer(erros, 6);
    

		printf("\nDigite uma palavra: \n\n\n");
		scanf (" %[^\t\n]47s", &palavra);
		limpar_input();
	
	
		trimEnd(palavra);

	int i;    
    for (i = 0; palavra[i] != 0; i++) {//Faz o tracejado da palavra
        char c = palavra[i];
        forca[i] = ehLetra(c) ? '_ ' : c;
    }
    //palavra = (char*)realloc(palavra, i*sizeof(char));
    //forca = (char*)realloc(palavra, i*sizeof(char));
   
}


int jogo(void) {//Jogo em si
    char tentativa;//Numero de Tentativas
    int chances = 6;//Numero de Chances
    int tent;

    int letras = 0;//Quandidade de letras
    int i;
    for (i = 0; palavra[i] != 0; i++) {//Conta quantas letras em a palavra
        if (ehLetra(palavra[i])) letras++;
    }

    while (chances > 0) {//Mantem o jogo rodando enquanto ainda houverem chances
        limpar_tela();
        printf("\nChances: %d - palavras tem %d letras\n\n", chances, letras);//Exibidor

		boneco(chances);

        printf("%s", forca);
        if (strlen(erros) > 0) {
            printf("\nErros: %s", erros);
        }

        printf("\n\nDigite uma letra: ");
        scanf("%c", &tentativa);//Requisita a letra(receberá caracter) 
        limpar_input();

        // Se o usuário digitou algo que não é letra, apenas insiste sem queimar uma chance.
        if (!ehLetra(tentativa)) continue;

        // Se o usuário digitou algo que ele já tentou antes (seja errando ou acertando), apenas insiste sem queimar uma chance.
        int jaTentou = 0;
        for (i = 0; erros[i] != 0; i++) {
            if (erros[i] == maiuscula(tentativa)) {
                jaTentou = 1;
                break;
            }
        }
        if (jaTentou) continue;
        for (i = 0; forca[i] != 0; i++) {
            if (maiuscula(forca[i]) == maiuscula(tentativa)) {
                jaTentou = 1;
                break;
            }
        }
        if (jaTentou) continue;

        int ganhou = 1;
        int achou = 0;
        for (i = 0; palavra[i] != 0; i++) {
            if (!ehLetra(palavra[i])) continue;
            if (forca[i] == '_') {
                if (maiuscula(palavra[i]) == maiuscula(tentativa)) {
                    forca[i] = palavra[i];
                    achou = 1;
                } else {
                    ganhou = 0;
                }
            }
        }
        

        if (ganhou) {
            return 1; //Usuario vence
        }

        if (!achou) {
            chances--;
            erros[strlen(erros)] = maiuscula(tentativa);
            
        }
    }
    limpar_tela();
    boneco(chances);
    return 0; //Usuario perde
}

int mostrarResultado(int resultado){
	int soma;
    limpar_input();
    if (resultado == 0) {
    	system("Color 40");
        printf("\nYou Morto Man. \nA palavra era: %s\n", palavra);
        printf("    _____         \n");
		printf("   /               \\       \n"); 
		printf("  /                 \\      \n");
		printf("//                   \\/\\  \n");
		printf("\\|   XXXX     XXXX   | /   \n");
		printf(" |   XXXX     XXXX   |/     \n");
		printf(" |   XXX       XXX   |      \n");
		printf(" |                   |      \n");
		printf(" \\__      XXX      __/     \n");
		printf("   |\\     XXX     /|       \n");
		printf("   | |           | |        \n");
		printf("   | I I I I I I I |        \n");
		printf("   |  I I I I I I  |        \n");
		printf("   \\_             _/       \n");
		printf("     \\_         _/         \n");
		printf("       \\___/           \n");
        return 0;
        
    } else {
        printf("\nVoce acertou a palavra: %s", palavra);
        printf("\nParabéns, você ganhou!\n\n");

		printf("          _____      \n");
		printf("      	'.=====.'     \n");
		printf("     .-\\:       /-.    \n");
		printf("     | (|:.     |)|     \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         .'   '.        \n");
		printf("        '-------'       \n\n");
        
        return 1;
    }
}

void BUFFER(char *buf, int tamanho){//Limpa o Buffer
    int i = 0;
    for (i = 0; i < tamanho; i++) {
        buf[i] = 0;
    }
}

int LETRA(char c) {//Indica que letras maiusculas e minusculas são equivalentes
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

void boneco(int contador){
  

        switch(contador)
        {
        case 6:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|          \n|.|        \ \n|.|         \n|.| \n|.| \n|.| \n\n");
            break;

        case 5:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|         \n|.|       \n|.| \n|.| \n|.| \n\n");
            break;

        case 4:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|         |    \n|.|         \n|.| \n|.| \n|.| \n\n");
            break;

        case 3:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|    \n|.|         \n|.| \n|.| \n|.| \n\n");
            break;

        case 2:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|\\    \n|.|         \n|.| \n|.| \n|.| \n\n");
            break;

        case 1:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|\\    \n|.|        /  \n|.|  \n|.|  \n|.| \n\n");
            break;
        case 0:
            printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|\\    \n|.|        / \\ \n|.|  \n|.|  \n|.| \n\n");
            break;
        }
}

