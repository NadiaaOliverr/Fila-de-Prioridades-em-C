//Declara��o das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //para utilizar a setlocale()
#include <time.h>
#include <conio.h> //para utilizar o getch()
#include <ctype.h> //para utilizar o isdigit()
#include <string.h> //para utilizar strcpy(), strcmp()

//Prot�tipo das fun��es
void menu_inicial();
void menu_modo_alerta();
int escolha_do_menu_inicial();
int adicionar_elementos();
void altera_numero_da_turma();


int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Portuguese"); //Permite acentua��o no console
    system("COLOR 0A");

    //Declara��o de vari�veis
    int retorno_menu_inicial;
    int retorno_adicionar_elementos;

    //Chamando fun��es
    menu_inicial();

    retorno_menu_inicial = escolha_do_menu_inicial();

    if(retorno_menu_inicial==1)
    {
        retorno_adicionar_elementos = menu_adicionar_elementos();
        printf("Quantidade: %d\n",retorno_adicionar_elementos);
    }
    else if(retorno_menu_inicial==2)
    {
        system("cls");
        printf("Ainda n�o implementado.\n");
        exit(1);
    }
    else if(retorno_menu_inicial==3)
    {
        system("cls");
        printf("Ainda n�o implementado.\n");
        exit(1);
    }
    else if(retorno_menu_inicial==4)
    {
        system("cls");
        printf("Ainda n�o implementado.\n");
        exit(1);
    }
    else if(retorno_menu_inicial==5)
    {
        system("cls");
        printf("Ainda n�o implementado.\n");
        exit(1);
    }
    else if(retorno_menu_inicial==6)
    {
        altera_numero_da_turma();
    }
    else if(retorno_menu_inicial==7)
    {
        system("cls");
        menu_modo_alerta();
    }
    else if(retorno_menu_inicial==8)
    {
        int i =0;
        for(i=0; i<=100; i++)//laco de repeticao de zero a 100.
        {
            system("cls");
            printf("              	 ___________________________________________________");
            printf("\n \t\t|\t\t     Saindo do sistema              |");
            printf("\n            	|___________________________________________________|");
            printf("     %d%% ",i);

        }

        system("cls");	//limpa a tela
        Sleep(100);//espera de um segundo
        printf("Sistema deslogado.\n");

    }

    return 0;
}
void altera_numero_da_turma()
{

    int i=0,z=0,t=0,d,x,encontrou=0; 

    char turma[100]; //vari�vel de entrada
    int turmanovo; //Vari�vel de entrada

    int tam; //Para ver o tamanho da palavra que foi inserida na entrada "turma", para posterior aloca��o na var�vel aux
    char* token; //Recebe o argumento que servir� de token para quebrar a string digitada na vari�vel "turma"

    //Vari�veis para ler do arquivo
    char nome_da_turma[100];
    int quantidade;
    int ano;
	
    //Vari�veis auxiliares para quebra da turma digitada
    char* aux; //C�pia da turma para aux, ou seja turma = aux
    char aux2[100];
    char aux3[10]; 


    //Cria��o de arquivos
    FILE *alunos_por_turma;
    FILE *alunos_por_turma_aux;



    alunos_por_turma = fopen("N�meros de alunos por turma.txt","r");
    alunos_por_turma_aux = fopen("Novo n�meros de alunos por turma.txt","w");
    if(alunos_por_turma==NULL)
    {
        printf("Arquivo inexistente.\n");
        exit(1);
    }
    if(alunos_por_turma_aux==NULL)
    {
        printf("Arquivo inexistente.\n");
        exit(1);
    }

    printf("Qual turma gostaria de alterar a quantidade de alunos?\n");
    gets(turma);


    tam = strlen(turma); 
    aux = (char*)malloc(tam * sizeof(char));
    strcpy(aux,turma);


    token = strtok(aux, " ");
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

    x = atoi(aux3); //Converte o char armazenado na vari�vel aux3 em inteiro
    
    
    
    while( (fscanf(alunos_por_turma,"%d %s %d\n", &ano, nome_da_turma, &quantidade))!=EOF ) //L� o txt at� encontrar o fim do arquivo
    {
        if(ano==x)
        {
            if(strcmp(nome_da_turma,aux2)==0)
            {
            	for(i=0;i<strlen(nome_da_turma);i++)
            	{
            		nome_da_turma[i]  = toupper(nome_da_turma[i]); // Converte caracter min�sculo em mai�sculo para aparecer para o usu�rio destacado
            	}
            	
            	printf("\nO tamanho atual da turma %s �: %d alunos!\n",nome_da_turma,quantidade);
                printf("\nQual o novo n�mero de alunos dessa turma?\n");
                scanf("%d",&turmanovo);
                
                for(i=0;i<strlen(nome_da_turma);i++)
            	{
            		nome_da_turma[i]  = tolower(nome_da_turma[i]); // Converte caracter mai�sculo em min�sculo para gravar no arquivo
            	}

                fprintf(alunos_por_turma_aux,"%d %s %d\n", ano,nome_da_turma,turmanovo);
                d = 1;
                encontrou = 1;
            }
            else
            {
                d=0;
            }
        }
        if(d==1)
        {
            d=0;
        }
        else
        {
            fprintf(alunos_por_turma_aux,"%d %s %d\n", ano,nome_da_turma,quantidade);
        }
    }

    if(!encontrou)
    {
        printf("A turma informada n�o se encontra no arquivo.\n");
    }
    else if(encontrou)
    {
    	printf("Alterado com sucesso.\n");
	}

    fclose(alunos_por_turma);

    alunos_por_turma = fopen("N�meros de alunos por turma.txt","w");
    
    fclose(alunos_por_turma_aux);

    alunos_por_turma_aux = fopen("Novo n�meros de alunos por turma.txt","r");


    while( (fscanf(alunos_por_turma_aux,"%d %s %d\n", &ano, nome_da_turma, &quantidade))!=EOF ) //L� o txt at� encontrar o fim do arquivo
    {
        fprintf(alunos_por_turma,"%d %s %d\n", ano,nome_da_turma,quantidade);
    }
    fclose(alunos_por_turma_aux);
    remove("Novo n�meros de alunos por turma.txt"); //Remove o arquivo auxiliar
    fclose(alunos_por_turma);
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


    alunos_por_turma = fopen("N�meros de alunos por turma.txt","r");
    if(alunos_por_turma==NULL)
    {
        printf("Arquivo inexistente.\n");
        exit(1);
    }

    printf("Quantos elementos ser�o adicionados na fila?.\n");
    scanf("%d",&tamanho);

    for(i=0; i<tamanho; i++)
    {
        fflush(stdin);
        printf("Nome: ");
        gets(nome); //alterar para o scanf com espa�o
        printf("Quantidade de folhas: ");
        scanf("%d",&folhas);
        fflush(stdin);
        printf("Turma: ");
        gets(turma);
        tam = strlen(turma); //Verifica o tamanho da string para posterior aloca��o na vari�vel auxiliar para busca no arquivo
        aux = (char*)malloc(tam * sizeof(char));
        strcpy(aux,turma); //faz a c�pia da turma digitada para vari�vel que servir� de compara��o para verificar a exist�ncia no arquivo


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



        while( (fscanf(alunos_por_turma,"%d %s %d\n", &ano, nome_da_turma, &quantidade))!=EOF ) //L� o txt at� encontrar o fim do arquivo
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
            printf("N�o existe no arquivo.\n");
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
    printf("\n\t FILA DE IMPRESS�O ESCOLA ADIRON GON�ALVES BOAVENTURA \n");
    printf("\t\t  Hor�rio do sistema: %s\n",timeStr);
    printf("\t\t\t    ");
    system("date /t");
    printf("\n   --------------------------------------------------------------\n");
    printf("   |\t[1] - Adicionar elementos a fila de impress�o.          |\n");
    printf("   |\t[2] - Verificar fila de impress�o da impressora A.      |\n");
    printf("   |\t[3] - Verificar fila de impress�o da impresora B.       |\n");
    printf("   |\t[4] - Verificar toda fila de impress�o.                 |\n");
    printf("   |\t[5] - Remover algum elemento da fila de impress�o.      |\n");
    printf("   |\t[6] - Alterar n�mero de alunos de uma turma.            |\n");
    printf("   |\t[7] - Modo alerta.                                      |\n");
    printf("   |\t[8] - Sair.                                             |");
    printf("\n   --------------------------------------------------------------\n");
}
int escolha_do_menu_inicial()
{

    char digitado[50];
    char c;//armazena cada caractere digitado pelo usu�rio
    int i=0;
    int escolha=0;//vari�vel para armazenar a convers�o do que foi digitado pelo usu�rio
    int cont=0;


    do
    {
        if(cont==0)
        {

            printf("\t\t       Opcao desejada: ");
            c=getch();//captura o caractere digitado pelo usu�rio
            printf("%c\n",c);

            //isdigit verifica se o que foi digitado � um n�mero ou n�o, retornando qualquer n�mero diferente de 0, se for um n�mero

            if (isdigit(c)!=0)	//se for um n�mero
            {
                digitado[i] = c;//armazena no vetor de caracteres
                i++;
            }
            else if(c==8 && i)//se for pressionada a tecla BACKSPACE e houver caracteres j� digitados, ou seja, i!=0
            {
                digitado[i]='\0';//o �ndice atual do vetor de caracteres recebe a termina��o da string
                i--;
                printf("\b \b");//o caractere digitado � apagado da tela, primeiro \b apaga o caracter da tela e o segundo \b tira o caracter da tela
            }
        }
        else
        {

            printf("\t\t       Digite uma op��o v�lida: ");
            c=getch();//captura o caractere digitado pelo usu�rio
            printf("%c\n",c);

            //isdigit verifica se o que foi digitado � um n�mero ou n�o, retornando qualquer n�mero diferente de 0, se for um n�mero

            if (isdigit(c)!=0)	//se for um n�mero
            {
                digitado[i] = c;//armazena no vetor de caracteres
                i++;
            }
            else if(c==8 && i)//se for pressionada a tecla BACKSPACE e houver caracteres j� digitados, ou seja, i!=0
            {
                digitado[i]='\0';//o �ndice atual do vetor de caracteres recebe a termina��o da string
                i--;
                printf("\b \b");//o caractere digitado � apagado da tela, primeiro \b apaga o caracter da tela e o segundo \b tira o caracter da tela
            }
        }
        cont ++;
    }
    while(c<'1' || c>'8');


    digitado[i]='\0';	//o �ndice atual do vetor de caracteres recebe a termina��o da string

    int tam = strlen(digitado);

    //atoi converte char para int
    escolha = atoi(&digitado[tam-1]); //atoi() tem como um par�metro um ponteiro para caracteres, por isso, pra usar com vetor tem que usar o &

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
    printf("\n\t FILA DE IMPRESS�O ESCOLA ADIRON GON�ALVES BOAVENTURA \n");
    printf("\t\t  Hor�rio do sistema: %s\n",timeStr);
    printf("\t\t\t    ");
    system("date /t");
    printf("\n   --------------------------------------------------------------\n");
    printf("   |\t[1] - Adicionar elementos a fila de impress�o.          |\n");
    printf("   |\t[2] - Verificar toda fila de impress�o.                 |\n");
    printf("   |\t[3] - Remover algum elemento da fila de impress�o.      |\n");
    printf("   |\t[4] - Alterar n�mero de alunos de uma turma.            |\n");
    printf("   |\t[5] - Modo normal.                                      |\n");
    printf("   |\t[6] - Sair.                                             |");
    printf("\n   --------------------------------------------------------------\n");

}