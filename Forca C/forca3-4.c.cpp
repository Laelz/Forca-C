#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "jogo.h"


int menu();
int cadastro();
int creditos();
void trimEnd();
int ehLetra();
char maiuscula();
void start();
int jogo();
void mostrarResultado();
int escolha();
void boneco(int contador);
void ranking(char *nome, char *pontuacao);
void limpaBuf();
void mostrarRanking();

enum modo_de_jogo{
	SAIR = 0,
	JOGAR,
	RANKING,
	CREDITOS
};

int main(){
	setlocale(LC_ALL, "Portuguese");
    
    menu();
    
    return 0;
}

int menu(){
	inimenu:
	char nome[30];
	char pontuacao[3];
	
	int resultado;
    int point[2];
	
	int op;
	
	
	printf(
	" +----------------------------------------------------------------------+\n"
	" |   o__ __o__/_                                                        |\n"                                                 
	" |  <|    v                                                             |\n"                                                  
	" |  < >                                                                 |\n"                                                         
	" |   |              o__ __o    \\o__ __o       __o__     o__ __o/        |\n" 
	" |   o__/_         /v     v\\    |     |>     />  \\     /v     |         |\n"  
	" |   |            />       <\\  / \\   < >   o/         />     / \\        |\n" 
	" |  <o>           \\         /  \\o/        <|          \\      \\o/        |\n" 
	" |   |             o       o    |          \\\\          o      |         |\n"  
	" |  / \\            <\\__ __/>   / \\          _\\o__</    <\\__  / \\        |\n"
	" +----------------------------------------------------------------------+\n" 
	"                               1 - Jogar\n"
	"                            2 - Ver Ranking\n"
	"                             3 - Créditos\n" 
	"                               0 - Sair\n"
	"\nOpção: ");
	op = escolha();
	switch(op){
		
		case SAIR:
			printf("Sucesso ao sair!");
			return EXIT_SUCCESS;
		break;
		
		case JOGAR:
			limpar_tela();
    		int multi;
    		printf("Digite 1 para:\t\tDigite 2 para:\nSingle Player\t\tMultiplayer\n\n");
    		scanf("%d", &multi);
    
  			  
			if (multi == 1){
    			int point[2];
    			int resultado;
    			do{
					start();
	    			resultado = jogo();
    				point[0] = mostrarResultado(resultado);
    				point[1] = point[1] + point[0];
    				printf("\nSeu resultado: %d\n", point[1]);
    				system("PAUSE");
				}while(resultado != 0);
				
				printf("Informe seu nome: ");
				scanf(" %[^\t\n]s", &nome);
			
				itoa(point[1], pontuacao, 3);
			
				ranking(nome, pontuacao);
	    	 	//cole aquui
			}else if(multi == 2){
				
				int vez;
				int point[4];
    			int resultado[2];
				for(vez = 0; vez < 2; vez++){
					int total = 0; 
				do{
    				start();
    				resultado[vez] = jogo();
   		 			point[2] = mostrarResultado(resultado[vez]);
   		 			total = total + point[2];
   		 			point[vez] = total; 
  				  	printf("Player %d\nSeu resultado: %d\n", vez+1, point[vez]);
    				system("PAUSE");
				}while(resultado[vez] != 0);
				}
		
				if(point[0] < point[1]){
					printf("\n\n\n\n\t\t\tPlayer 2 foi o vencedor");
				}else{
					printf("\n\n\n\n\t\t\tPlayer 1 foi o vencedor");
				}
			}else{
				printf("Opção inválida");
			}
			
    		//free(palavra);
    		//free(forca);
		break;
		
		case RANKING:
			mostrarRanking();
			system("PAUSE");
			system("cls");
			goto inimenu;
		break;
		
		case CREDITOS:
			creditos();
			system("PAUSE");
			system("cls");
			goto inimenu;
		break;
		
		default:
			printf("Opção inválida!");
		break;	
	}
	
	return EXIT_SUCCESS;
}

int creditos(){
printf(
	"	  	   	  o--------------------o\n"
	"                          |     Jose Lopes     |\n"
	"                          |  Lael Alburquerque |\n"
	"                          |     Lucas Alves    |\n"
	"		          o--------------------o\n" 
	);
}

int escolha(){
	
	int escolher;
	scanf("%d",&escolher);
	printf("Escolha = %d\n\n", escolher);
	return escolher;
}

void ranking(char *nome, char *pontuacao)
{
	
	FILE * arquivo = NULL;
	arquivo = fopen("ranking.txt", "a+");	
	fprintf(arquivo, nome);
	fprintf(arquivo, ",");

	fprintf(arquivo, pontuacao);
	fprintf(arquivo, "\n");
	
	fclose(arquivo);	
}

void limpaBuf(){
	char c;
while((c = getchar()) != '\n' && c != EOF);
}

void mostrarRanking() {
	system("cls");
	printf("\t\tRANKING:\n\n");
	char * line;
    // Abre arquivo.
    FILE *fp = fopen("ranking.txt", "r");
    size_t len = 255;
    //Alocando memória para linha.
	line = (char*)malloc(sizeof(char) * len);
    //Verifica a existência do arquivo para abri-lo ou não.
    if (fp == NULL) {
        //Se for vazio retorna a mensagem de erro
        printf("Ranking vazio no momento.\n\n");
        return;
    }
    while(fgets(line, len, fp) != NULL) {
        printf("%s", line);
    }
    free(line);
}

