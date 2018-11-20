//Declaração das bibliotecas
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h> //para utilizar o getch()
#include <ctype.h> //para utilizar o isdigit()
#include <string.h>

//Protótipo das funções
void menu_inicial();
void menu_modo_alerta();
int escolha_do_menu_inicial();
int menu_adicionar_elementos();
void altera_numero_da_turma();

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "portuguese"); //Permite acentuação no console
    //system("MODE con cols=70 lines=30"); //Ajusta a largura e altura da tela
    system("COLOR 0A");

    //Declração de variáveis
    int retorno;
    int retornoz;


    menu_inicial();
    retorno = escolha_do_menu_inicial();
    if(retorno==6)
    {
        altera_numero_da_turma();
    }
    if(retorno==1)
    {

        retornoz = menu_adicionar_elementos();
        printf("quant: %d\n",retornoz);
    }

    else if(retorno==7)
    {
        system("cls");
        menu_modo_alerta();
    }

    return 0;
}
void altera_numero_da_turma()
{

    int i=0,j=0,tamanho,tam, folhas;
    char nome[100];
    char turma[100];
    FILE *alunos_por_turma;
    int quantidade,ano;
    char nome_da_turma[100];
    char* aux;
    int teste;
    char aux2[100];
    char aux3[10];

    char* token;

    alunos_por_turma = fopen("Números de alunos por turma.txt","r");
    if(alunos_por_turma==NULL)
    {
        printf("Arquivo inexistente.\n");
        exit(1);
    }

    printf("Qual turma gostaria de alterar a quantidade de alunos?");
    gets(turma);
//	printf("A quantidade de alunos da tuma é: %d\n",(*x));



    int turmanovo;



    tam = strlen(turma); //Verifica o tamanho da string para posterior alocação na variável auxiliar para busca no arquivo
    aux = (char*)malloc(tam * sizeof(char));
    strcpy(aux,turma); //faz a cópia da turma digitada para variável que servirá de comparação para verificar a existência no arquivo


    token = strtok(aux, " ");
    int t=0;
    while (token != NULL)
    {

        if(t==0)
        {
            strcpy(aux3,token);
        }
        strcpy(aux2,token);

        token = strtok(NULL, " ");
        t++;

    }

    int x = atoi(aux3);
    int y=0;
    int z=0;
    int d;

    FILE *alunos_por_turma1;

    alunos_por_turma1 = fopen("Novo números de alunos por turma.txt","w");
    fclose(alunos_por_turma);
                alunos_por_turma = fopen("Números de alunos por turma.txt","r");

    while( (fscanf(alunos_por_turma,"%d %s %d\n", &ano, nome_da_turma, &quantidade))!=EOF ) //Lê o txt até encontrar o fim do arquivo
    {


        if(ano==x)
        {
            if(strcmp(nome_da_turma,aux2)==0)
            {
                printf("Qual o novo número de alunos dessa turma?\n");
                scanf("%d",&turmanovo);

				fprintf(alunos_por_turma1,"%d %s %d\n", ano,nome_da_turma,turmanovo);
				d = 1;
                
            }
            else
            {
            	d =0;
                y++;
            }
        }
        
        j++;
        if(d==1)
        {
        	continue;
        }else{
        fprintf(alunos_por_turma1,"%d %s %d\n", ano,nome_da_turma,quantidade);
    }
    }
    if(y==j)
    {
        z = 0;
        printf("Não existe no arquivo.\n");
    }

    		    fclose(alunos_por_turma);
                alunos_por_turma = fopen("Números de alunos por turma.txt","w");
                fclose(alunos_por_turma1);

				alunos_por_turma1 = fopen("Novo números de alunos por turma.txt","r");


    while( (fscanf(alunos_por_turma1,"%d %s %d\n", &ano, nome_da_turma, &quantidade))!=EOF ) //Lê o txt até encontrar o fim do arquivo
    {
    	//printf("%d %s %d\n",ano,nome_da_turma,quantidade);

				fprintf(alunos_por_turma,"%d %s %d\n", ano,nome_da_turma,quantidade);

	}
	fclose(alunos_por_turma1);
	remove("Novo números de alunos por turma.txt");

}


int menu_adicionar_elementos()
{

    int i=0,j=0,tamanho,tam, folhas;
    char nome[100];
    char turma[100];
    FILE *alunos_por_turma;
    int quantidade,ano;
    char nome_da_turma[100];
    char* aux;
    int teste;
    char aux2[100];
    char aux3[10];

    char* token;


    alunos_por_turma = fopen("Números de alunos por turma.txt","r");
    if(alunos_por_turma==NULL)
    {
        printf("Arquivo inexistente.\n");
        exit(1);
    }

    printf("Quantos elementos serão adicionados na fila?.\n");
    scanf("%d",&tamanho);

    for(i=0; i<tamanho; i++)
    {
        fflush(stdin);
        printf("Nome: ");
        gets(nome); //alterar para o scanf com espaço
        printf("Quantidade de folhas: ");
        scanf("%d",&folhas);
        fflush(stdin);
        printf("Turma: ");
        gets(turma);
        tam = strlen(turma); //Verifica o tamanho da string para posterior alocação na variável auxiliar para busca no arquivo
        aux = (char*)malloc(tam * sizeof(char));
        strcpy(aux,turma); //faz a cópia da turma digitada para variável que servirá de comparação para verificar a existência no arquivo


        token = strtok(aux, " ");
        int t=0;
        while (token != NULL)
        {

            if(t==0)
            {
                strcpy(aux3,token);
            }
            strcpy(aux2,token);

            token = strtok(NULL, " ");
            t++;

        }

        int x = atoi(aux3);
        int y=0;
        int z=0;



        while( (fscanf(alunos_por_turma,"%d %s %d\n", &ano, nome_da_turma, &quantidade))!=EOF ) //Lê o txt até encontrar o fim do arquivo
        {

            if(ano==x)
            {
                if(strcmp(nome_da_turma,aux2)==0)
                {
                    z = quantidade;
                    y--;
                    return z;

                }
                else
                {
                    y++;
                }
            }
            else
            {
                y++;
            }
            j++;
        }
        if(y==j)
        {
            z = 0;
            printf("Não existe no arquivo.\n");
            return z;
        }
    }
}

void menu_inicial()
{

    char dateStr[9];
    char timeStr[9];

    _strdate(dateStr);
    _strtime(timeStr);
    printf("\n\t FILA DE IMPRESSÃO ESCOLA ADIRON GONÇALVES BOAVENTURA \n");
    printf("\t\t  Horário do sistema: %s\n",timeStr);
    printf("\t\t\t    ");
    system("date /t");
    printf("\n   --------------------------------------------------------------\n");
    printf("   |\t[1] - Adicionar elementos a fila de impressão.          |\n");
    printf("   |\t[2] - Verificar fila de impressão da impressora A.      |\n");
    printf("   |\t[3] - Verificar fila de impressão da impresora B.       |\n");
    printf("   |\t[4] - Verificar toda fila de impressão.                 |\n");
    printf("   |\t[5] - Remover algum elemento da fila de impressão.      |\n");
    printf("   |\t[6] - Alterar número de alunos de uma turma.            |\n");
    printf("   |\t[7] - Modo alerta.                                      |\n");
    printf("   |\t[8] - Sair.                                             |");
    printf("\n   --------------------------------------------------------------\n");
}
int escolha_do_menu_inicial()
{

    char digitado[50];
    char c;//armazena cada caractere digitado pelo usuário
    int i=0;
    int escolha=0;//variável para armazenar a conversão do que foi digitado pelo usuário
    int cont=0;


    do
    {
        if(cont==0)
        {

            printf("\t\t       Opcao desejada: ");
            c=getch();//captura o caractere digitado pelo usuário
            printf("%c\n",c);

            //isdigit verifica se o que foi digitado é um número ou não, retornando qualquer número diferente de 0, se for um número

            if (isdigit(c)!=0)	//se for um número
            {
                digitado[i] = c;//armazena no vetor de caracteres
                i++;
            }
            else if(c==8 && i)//se for pressionada a tecla BACKSPACE e houver caracteres já digitados, ou seja, i!=0
            {
                digitado[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
                i--;
                printf("\b \b");//o caractere digitado é apagado da tela, primeiro \b apaga o caracter da tela e o segundo \b tira o caracter da tela
            }
        }
        else
        {

            printf("\t\t       Digite uma opção válida: ");
            c=getch();//captura o caractere digitado pelo usuário
            printf("%c\n",c);

            //isdigit verifica se o que foi digitado é um número ou não, retornando qualquer número diferente de 0, se for um número

            if (isdigit(c)!=0)	//se for um número
            {
                digitado[i] = c;//armazena no vetor de caracteres
                i++;
            }
            else if(c==8 && i)//se for pressionada a tecla BACKSPACE e houver caracteres já digitados, ou seja, i!=0
            {
                digitado[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
                i--;
                printf("\b \b");//o caractere digitado é apagado da tela, primeiro \b apaga o caracter da tela e o segundo \b tira o caracter da tela
            }
        }
        cont ++;
    }
    while(c<'1' || c>'8');


    digitado[i]='\0';	//o índice atual do vetor de caracteres recebe a terminação da string

    int tam = strlen(digitado);

    //atoi converte char para int
    escolha = atoi(&digitado[tam-1]); //atoi() tem como um parâmetro um ponteiro para caracteres, por isso, pra usar com vetor tem que usar o &

    return escolha;
}
void menu_modo_alerta()
{

    char dateStr[9];
    char timeStr[9];
    system("COLOR 17");
    Beep(1000,1700);
    sleep(0);
    system("COLOR 07");
    _strdate(dateStr);
    _strtime(timeStr);
    printf("\n\t FILA DE IMPRESSÃO ESCOLA ADIRON GONÇALVES BOAVENTURA \n");
    printf("\t\t  Horário do sistema: %s\n",timeStr);
    printf("\t\t\t    ");
    system("date /t");
    printf("\n   --------------------------------------------------------------\n");
    printf("   |\t[1] - Adicionar elementos a fila de impressão.          |\n");
    printf("   |\t[2] - Verificar toda fila de impressão.                 |\n");
    printf("   |\t[3] - Remover algum elemento da fila de impressão.      |\n");
    printf("   |\t[4] - Alterar número de alunos de uma turma.            |\n");
    printf("   |\t[5] - Modo normal.                                      |\n");
    printf("   |\t[6] - Sair.                                             |");
    printf("\n   --------------------------------------------------------------\n");

}
