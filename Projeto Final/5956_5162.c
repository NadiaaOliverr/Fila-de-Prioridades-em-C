// O arquivo 5956_5162.rar é composto pelo "Leia-me.pdf", 2 cartões de visita ( Nádia e Júlia, ambos png ), Caracteres Ascii Utilizados no código.png
//5956_5162.doc ( que se trata do enunciado em relaçao a esta codificação ), Números de alunos por turma.txt ( imprescindível para compilação deste código em
//questão ) e por fim, o código atual, 5956_5162.c


//BIBLIOTECAS NECESSÁRIAS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //para utilizar o time();
#include <conio.h> //para utilizar o getch();
#include <ctype.h> //para utilizar o isdigit();
#include <string.h> //para utilizar strcpy(), strcmp();


//TAD FILA DE PRIORIDADE
typedef struct scelula
{
    char nome_elemento[50];
    char nome_da_turma[50];
    int prioridade; //a prioridade é o tempo gasto para imprimir o arquivo
    struct scelula* prox;
} Celula;

typedef struct sfila
{
    Celula *inicio;
    Celula* fim;
} Fila;


//Protótipo das funções
void menu_inicial();
void menu_modo_alerta();
int escolha_do_menu_inicial();
int escolha_menu_alerta();
int escolha_de_tamanho();
int escolha_de_imprimir();
int quantidade_de_folhas();
int quantidade_de_alunos(char turma[]);
void altera_numero_da_turma();


//Funções prórias de Fila
int vazia(Fila *f);
Celula* criar_no();
void inicializa(Fila *f);
void insere_na_fila(Fila* a, Fila* b, char nome[],char turma[], int tempo);
void imprime (Fila* f, Fila *g);      //função recursiva
int contar_elementos_fila(Fila *f,Fila *g);
void desenfileirar(Fila *fila);
void insere_fila_aux(Fila *a);
void enfileirar(Fila* f, char turma[], char nome[],int tempo);
void lista_da_imprime(Fila *f,Celula** lista);
int pesquisar_fila(Fila* fila, char nome[],char turma[]);
void redistribuir(Celula* lista, Fila* a, Fila* b); //pra redistribuir o que tiver no modo alerta nas filas do modo normal
void transferencia_lista_fila(Celula* lista, Fila* fila);//passar o que tiver nas 'filas' para a fila completa

//Funções de lista para quando uma lista auxiliar for utilizada
int lista_vazia(Celula* lista);
void imprime_lista(Celula* lista);
void insere_na_lista(Celula** lista,char nome[],char turma[], int tempo);
int remover_da_lista(Celula** lista, char nome[], char turma[]);
Celula* pesquisar_lista(Celula* lista, char nome[],char turma[]);
int contar_elementos_da_lista(Celula *lista);
int mover_pra_frente(Celula **lista);
void transferencia_fila_lista(Fila *fila, Fila* auxiliar, Celula** lista);





//-------------------------------------------------------MAIN---------------------------------------------------------------------------

int main()
{

    system("COLOR 0A"); //Muda a cor do terminal
    system("title FIFO Priority Printing"); //Muda o nome da janela

    //Declaração de variáveis
    int retorno_menu_inicial;
    int numero_alunos,folhas,tamanho,i, tempo,t;
    char nome[100];
    char nome_aux[100];
    char turma[100];
    char variavel_de_pausa;
    int retorno_menu_alerta=0;


    Celula *lista; //Par utilizar uma lista

    Fila filaA;
    Fila filaB;
    Fila auxiliar;


    //Inicializa lista auxiliar
    lista = NULL;

    //inicializando as filas de impressões
    inicializa(&filaA);
    inicializa(&filaB);

    //Fila auxiliar
    inicializa(&auxiliar);

    //Variáveis de controle
    int controle =1;
    int controle2=0;
    int controle_nome=0; //para escrever na tela que o nome foi digitado errado na volta do "do while"
    char espaco_nome = ' ';
    int tamanho_nome=1;
    int cont=0;
    char nome_aux1[100];

    int j;



    //Laço de repetição que chama o menu inicial e possibilita a escolha das operações de acordo com o querer do usuário
    do
    {

        if(controle2!=1)
        {

            menu_inicial();
            retorno_menu_inicial = escolha_do_menu_inicial();

        }

        //ADICIONAR ELEMENTOS A FILA DE IMPRESSÃO
        if(retorno_menu_inicial==1)
        {
            if(controle==1)
            {

                tamanho = escolha_de_tamanho();
                int contr=0;

                for(j=0; j<tamanho; j++)
                {
                    fflush(stdin);
                    do
                    {

                        if(controle_nome || contr)
                        {
                            controle_nome=0;
                            contr=0;
                        }
                        printf("Nome do Arquivo: ");
                        gets(nome);
                        strcpy(nome_aux,nome);
                        tamanho_nome= strlen(nome);

                        for(i=0; i<(tamanho_nome-1); i++)
                        {
                            if(nome[i]==' ')
                            {
                                cont++;
                            }
                        }
                        if(cont==tamanho_nome-1)
                        {
                            if(cont==0  && (tamanho_nome-1)==0)
                            {

                                contr=0;
                            }
                            else
                            {

                                contr = 1;
                            }
                        }
                        nome[tamanho-1]='\0';	 //Para decretar o fim da palavra para caso precise encontrar o tamanho novamente
                        controle_nome=1;
                        if(contr==1)
                        {
                            controle_nome=0;
                        }

                    }
                    while((strcmp(nome,&espaco_nome)==0) || tamanho_nome==0 || contr==1);
                    fflush(stdin);
                    folhas = quantidade_de_folhas();
                    printf("Turma: ");
                    fflush(stdin);
                    gets(turma);
                    numero_alunos = quantidade_de_alunos(turma);
                    if(numero_alunos==0)
                    {
                        printf("Turma n%co cadastrada.\nTente Novamente.\n",198);
                        sleep(1);
                        fflush(stdin);
                        do
                        {

                            if(controle_nome || contr)
                            {
                                controle_nome=0;
                                contr=0;
                            }
                            printf("Nome do Arquivo: ");
                            gets(nome);
                            strcpy(nome_aux,nome);
                            tamanho_nome= strlen(nome);

                            for(i=0; i<(tamanho_nome-1); i++)
                            {
                                if(nome[i]==' ')
                                {
                                    cont++;
                                }
                            }
                            if(cont==tamanho_nome-1)
                            {
                                if(cont==0  && (tamanho_nome-1)==0)
                                {

                                    contr=0;
                                }
                                else
                                {

                                    contr = 1;
                                }
                            }
                            nome[tamanho]='\0';	 //Para decretar o fim da palavra para caso precise encontrar o tamanho novamente
                            controle_nome=1;
                            if(contr==1)
                            {
                                controle_nome=0;
                            }

                        }
                        while((strcmp(nome,&espaco_nome)==0) || tamanho_nome==0 || contr==1);
                        fflush(stdin);
                        folhas = quantidade_de_folhas();
                        printf("Turma: ");
                        fflush(stdin);
                        gets(turma);
                        numero_alunos = quantidade_de_alunos(turma);
                    }

                    tempo = ( numero_alunos * folhas  ) ; //Cálculo do numero de alunos da turma * a quantidade de folhas do arquivo

                    if(numero_alunos!=0) //Para não gravar turmas não cadastradas no arquivo
                    {
                        insere_na_fila(&filaA,&filaB,nome_aux,turma,tempo);
                        insere_na_lista(&lista,nome_aux,turma,tempo);
                    }

                }
            }
            system("cls");
        }

        //VERIFICAR FILA DA IMPRESSORA A
        if(retorno_menu_inicial==2)
        {
            system("cls");
            Celula* aux;
            if(controle==1)
            {

                inicializa(&auxiliar);
                printf("\n\n\t\t\t\tQuantidade de elementos presentes na impressora A: %d\n",contar_elementos_fila(&filaA,&auxiliar));

                filaA = auxiliar;

                printf("\n\n\n\t\t\t\t\t ------> ELEMENTOS DA IMPRESSORA  A <------ \n\n");
                inicializa(&auxiliar); //inicializando novamente a auxiliar

                imprime(&filaA,&auxiliar);

                aux=auxiliar.inicio;
                while(aux!=NULL)
                {
                    enfileirar(&filaA,aux->nome_da_turma,aux->nome_elemento,aux->prioridade);
                    desenfileirar(&auxiliar);
                    aux=aux->prox;
                }

                printf("\nPressione ENTER para prosseguir...\n");
                scanf("%c",&variavel_de_pausa);
                controle2=0;
                system("cls");
            }

        }
        //VERIFICAR FILA DA IMPRESSORA B
        if(retorno_menu_inicial==3)
        {
            system("cls");
            Celula* aux;
            if(controle==1)
            {
                printf("\n\n\t\t\t\tQuantidade de elementos presentes na impressora B: %d\n",contar_elementos_fila(&filaB,&auxiliar));

                filaB = auxiliar;

                printf("\n\n\n\t\t\t\t\t ------> ELEMENTOS DA IMPRESSORA  B <------ \n\n");
                inicializa(&auxiliar); //inicializando novamente a auxiliar

                imprime(&filaB,&auxiliar);

                aux=auxiliar.inicio;
                while(aux!=NULL)
                {
                    enfileirar(&filaB,aux->nome_da_turma,aux->nome_elemento,aux->prioridade);
                    desenfileirar(&auxiliar);
                    aux=aux->prox;
                }

                printf("\nPressione ENTER para prosseguir...\n");
                scanf("%c",&variavel_de_pausa);
                controle2=0;
                system("cls");
            }
        }


        //VERIFICAR A LISTA COM TODOS OS ELEMENTOS
        if(retorno_menu_inicial==4)
        {
            system("cls");
            if(controle==1)
            {

                printf("Quantidade de elementos presente em AMBAS impressoras: %d\n",contar_elementos_da_lista(lista));


                printf("\n\n\n\t\t\t\t\t ------> ELEMENTOS DE AMBAS IMPRESSORAS  <------ \n\n");
                        	printf("\t\t\t\t\t       LISTA DE ARQUIVOS SENDO IMPRESSOS\n\n\n");
				imprime_lista(lista);


                printf("\nPressione enter para prosseguir...\n");
                scanf("%c",&variavel_de_pausa);
                controle2=0;
                system("cls");
            }
        }

        //REMOVER ALGUM ELEMENTO DA FILA DE IMPRESSÃO
        if(retorno_menu_inicial==5 && controle==1)
        {
        	if(!lista_vazia(lista)){

            imprime_lista(lista);
            printf("Qual elemento foi inserido incorretamente?\n");
            gets(nome);
            printf("Qual a turma deste elemento?\n");
            gets(turma);

            t=pesquisar_fila(&filaA,nome,turma);

            if(t==1)
                pesquisar_fila(&filaB,nome,turma);

            if(remover_da_lista(&lista,nome,turma)==1)
            {
                printf("\nRemovido com sucesso.\n");
            }


            printf("\nPressione ENTER para prosseguir...\n");
            scanf("%c",&variavel_de_pausa);
            system("cls");
        }else{
        	printf("Lista vazia.\n");
        	sleep(1);
		}
    }

        //ALTERAR NÚMERO DE ALUNOS DE UMA TURMA
        if(retorno_menu_inicial==6)
        {
            altera_numero_da_turma();
            Sleep(1500);
            system("cls");
        }

        //IMPRIMIR
        if(retorno_menu_inicial==7 && controle==1)
        {
            int escolha;
            do
            {

                system("cls");
                printf("\n   ----------------------------------------------------\n");
                printf("   |\t[1] - Imprimir a fila de impressora A.        |\n");
                printf("   |\t[2] - Imprimir a fila de impressora B.        |\n");
                printf("   |\t[3] - Imprimir ambas filas de impress%co.      |\n",198);
                printf("   |\t[4] - Voltar ao Menu anterior.                |");
                printf("\n   ----------------------------------------------------\n");
                escolha = escolha_de_imprimir();

                //IMPRESSORA A
                if(escolha==1)
                {
                    if(!vazia(&filaA))
                    {
                        int i =0;
                        char espaco[120]=""; //limpa o espaco reservado na memoria

                        int tempo = clock();

                        for(i=0; i<=100; i++)
                        {

                            if(i%2==0)
                            {
                                strcat(espaco,"Û");
                            }
                            system("CLS");//limpa a tela

                            printf("\t\t\t\t\t\t\tImpressora A\n\n");
                            printf("\t\t\t               ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                            printf("\n  Imprindo Arquivos de A ");


                            printf("\t\t  %s ",espaco);

                            printf("\n\t\t\t               ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");

                            printf("     %d%% ",i);
                            printf("\n\n\n\n\n\n\n");

                            if(i==0)
                            {
        						printf("\t\t\t\t\t       LISTA DE ARQUIVOS SENDO IMPRESSOS\n\n\n");
                                lista_da_imprime(&filaA,&lista);

                            }
                            sleep(1);

                        }
                    }
                    else
                    {
                        printf("\n\nA fila est%c vazia, tente novamente.\n",160);
                        sleep(2);
                    }
                    system("cls");
                }

                //IMPRESSORA B
                else if(escolha==2)
                {
                    if(!vazia(&filaB))
                    {
                        int i =0;
                        char espaco[120]=""; //limpa o espaco reservado na memoria

                        int tempo = clock();



                        for(i=0; i<=100; i++)
                        {

                            if(i%2==0)
                            {
                                strcat(espaco,"Û");
                            }
                            system("CLS");//limpa a tela

                            printf("\t\t\t\t\t\t\tImpressora B\n\n");
                            printf("\t\t\t               ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                            printf("\n  Imprindo Arquivos de B ");


                            printf("\t\t  %s ",espaco);

                            printf("\n\t\t\t               ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");

                            printf("     %d%% ",i);
                            printf("\n\n\n\n\n\n\n");

                            if(i==0)
                            {
							        	printf("\t\t\t\t\t       LISTA DE ARQUIVOS SENDO IMPRESSOS\n\n\n");
                                lista_da_imprime(&filaB,&lista);

                            }
                            sleep(1);

                        }
                    }
                    else
                    {
                        printf("\n\nA fila est%c vazia, tente novamente.\n",160);
                        sleep(2);
                    }
                    system("cls");
                }
                //AMBAS
                else if(escolha==3)
                {
                	int controle_f=0;
                	int controle_f1 =0;
                    if(!lista_vazia(lista))
                    {

                        int i =0;
                        char espaco[120]=""; //limpa o espaco reservado na memoria

                        int tempo = clock();

                        for(i=0; i<=100; i++)
                        {

                            if(i%2==0)
                            {
                                strcat(espaco,"Û");
                            }
                            system("CLS");//limpa a tela

                            if(!vazia(&filaA))
                            {
                            	controle_f = 1;
							}
							if(!vazia(&filaB))
							{
								controle_f1 = 1;
							}
                            if(i==0)
                            {
								printf("\t\t\t\t\t       LISTA DE ARQUIVOS SENDO IMPRESSOS\n\n\n");
                                lista_da_imprime(&filaA,&lista);
                                lista_da_imprime(&filaB,&lista);

                                sleep(3);

                            }

							if(controle_f && i!=0){
                            printf("\t\t\t\t\t\t\tImpressora A\n\n");
                            printf("\t\t\t               ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                            printf("\n  Imprindo Arquivos de A ");


                            printf("\t\t  %s ",espaco);

                            printf("\n\t\t\t               ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");

                            printf("     %d%% ",i);
                            printf("\n\n\n\n\n\n\n");
                        }

							 if(controle_f1 && i!=0){

                            printf("\t\t\t\t\t\t\tImpressora B\n\n");
                            printf("\t\t\t               ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                            printf("\n  Imprindo Arquivos de B ");


                            printf("\t\t  %s ",espaco);

                            printf("\n\t\t\t               ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");

                            printf("     %d%% ",i);
                            printf("\n\n\n\n\n\n\n");
                        }
                        sleep(1);

                        }

                    }
                    else
                    {
                        printf("\n\nA fila est%c vazia, tente novamente.\n",160);
                        sleep(2);
                    }
                    system("cls");
                }
                //MENU ANTERIOR
                else if(escolha==4)
                {
                    system("cls");
                }

            }
            while(escolha!=4);
        }

        //MODO ALERTA
        if(retorno_menu_inicial==8)
        {
            system("cls");
            system("COLOR 17");
            Beep(1000,1700);
            Fila filaMA;

            //inicializando a fila do modo alerta
            inicializa(&filaMA);

            //função que ordena a lista anterior
            mover_pra_frente(&lista);
            transferencia_lista_fila(lista,&filaMA);
            lista=NULL; //remove tudo que está na lista
            transferencia_fila_lista(&filaMA,&auxiliar,&lista);


            do
            {

                if(controle==6)
                {

                }
                else
                {

                    menu_modo_alerta();
                    retorno_menu_alerta = escolha_menu_alerta();
                    int contr=0;

                    //INSERE ELEMENTOS NA FILA
                    if(retorno_menu_alerta==1)
                    {

                        tamanho=escolha_de_tamanho();

                        for(j=0; j<tamanho; j++)
                        {
                            fflush(stdin);
                            do
                            {

                                if(controle_nome || contr)
                                {
                                    controle_nome=0;
                                    contr=0;
                                }
                                printf("Nome do Arquivo: ");
                                gets(nome);
                                strcpy(nome_aux1,nome);
                                tamanho_nome= strlen(nome);

                                for(i=0; i<(tamanho_nome-1); i++)
                                {
                                    if(nome[i]==' ')
                                    {
                                        cont++;
                                    }
                                }
                                if(cont==tamanho_nome-1)
                                {
                                    if(cont==0  && (tamanho_nome-1)==0)
                                    {

                                        contr=0;
                                    }
                                    else
                                    {

                                        contr = 1;
                                    }
                                }
                                nome[tamanho]='\0';	 //Para decretar o fim da palavra para caso precise encontrar o tamanho novamente
                                controle_nome=1;
                                if(contr==1)
                                {
                                    controle_nome=0;
                                }

                            }
                            while((strcmp(nome,&espaco_nome)==0) || tamanho_nome==0 || contr==1);


                            folhas = quantidade_de_folhas();
                            printf("Turma: ");
                            fflush(stdin);
                            gets(turma);
                            numero_alunos = quantidade_de_alunos(turma);

                            if(numero_alunos==0)
                   			 {
                        printf("Turma n%co cadastrada.\nTente Novamente.\n",198);
                        sleep(1);
                        fflush(stdin);
                        do
                        {

                            if(controle_nome || contr)
                            {
                                controle_nome=0;
                                contr=0;
                            }
                            printf("Nome do Arquivo: ");
                            gets(nome);
                            strcpy(nome_aux,nome);
                            tamanho_nome= strlen(nome);

                            for(i=0; i<(tamanho_nome-1); i++)
                            {
                                if(nome[i]==' ')
                                {
                                    cont++;
                                }
                            }
                            if(cont==tamanho_nome-1)
                            {
                                if(cont==0  && (tamanho_nome-1)==0)
                                {

                                    contr=0;
                                }
                                else
                                {

                                    contr = 1;
                                }
                            }
                            nome[tamanho]='\0';	 //Para decretar o fim da palavra para caso precise encontrar o tamanho novamente
                            controle_nome=1;
                            if(contr==1)
                            {
                                controle_nome=0;
                            }

                        }
                        while((strcmp(nome,&espaco_nome)==0) || tamanho_nome==0 || contr==1);
                        fflush(stdin);
                        folhas = quantidade_de_folhas();
                        printf("Turma: ");
                        fflush(stdin);
                        gets(turma);
                        numero_alunos = quantidade_de_alunos(turma);
                    }

                    tempo = ( numero_alunos * folhas  ) ; //Cálculo do numero de alunos da turma * a quantidade de folhas do arquivo
				}
                    if(numero_alunos!=0) //Para não gravar turmas não cadastradas no arquivo
                    {
                        enfileirar(&filaMA,turma,nome_aux,tempo);
                        insere_na_lista(&lista,nome_aux,turma,tempo);
                    }
                        system("cls");
                    }

                    //VERIFICAR A FILA
                    if(retorno_menu_alerta==2)
                    {

                        system("cls");
                        Celula *aux;

                        printf("\n\n\t\t\t\tQuantidade de elementos presentes na impressora: %d\n",contar_elementos_fila(&filaMA,&auxiliar));

                        filaMA = auxiliar;

                        printf("\n\n\n\t\t\t\t\t ------> ELEMENTOS A SEREM IMPRESSOS <------ \n\n");
                        inicializa(&auxiliar); //inicializando novamente a auxiliar

                        imprime(&filaMA,&auxiliar);

                        aux=auxiliar.inicio;
                        while(aux!=NULL)
                        {
                            enfileirar(&filaMA,aux->nome_da_turma,aux->nome_elemento,aux->prioridade);
                            desenfileirar(&auxiliar);
                            aux=aux->prox;
                        }

                        printf("\nPressione ENTER para prosseguir...\n");
                        scanf("%c",&variavel_de_pausa);
                        system("cls");
                    }

                    //REMOVE ELEMENTO DA FILA DE IMPRESSÃO
                    if(retorno_menu_alerta==3)
                    {
						if(!lista_vazia(lista)){

                        imprime_lista(lista);
                        printf("Qual elemento foi inserido incorretamente?\n");
                        gets(nome);
                        printf("Qual a turma deste elemento?\n");
                        gets(turma);
                        pesquisar_fila(&filaMA,nome,turma);
                        if(remover_da_lista(&lista,nome,turma)==1)
                        {
                            printf("\nRemovido com sucesso.\n");
                        }

                        printf("\nPressione enter para prosseguir...\n");
                        scanf("%c",&variavel_de_pausa);
                        system("cls");
                    }else {
                    	printf("Lista vazia.\n");
                    	sleep(1);
					}
                }

                    //ALTERAR NUMERO DE ALUNOS DA TURMA
                    if(retorno_menu_alerta==4)
                    {

                        altera_numero_da_turma();
                        Sleep(1500);
                        system("cls");
                    }

                    //IMPRIMIR
                    if(retorno_menu_alerta==5)
                    {

                        int escolha;
                        do
                        {

                            system("cls");
                            printf("\n   ----------------------------------------------------\n");
                            printf("   |\t[1] - Imprimir a fila de impress%co.          |\n",198);
                            printf("   |\t[2] - Voltar ao Menu anterior.                |");
                            printf("\n   ----------------------------------------------------\n");
                            escolha = escolha_de_imprimir();

                            if(escolha==1)
                            {
                                if(!lista_vazia(lista))
                                {
                                    int i =0;
                                    char espaco[120]=""; //limpa o espaco reservado na memoria

                                    int tempo = clock();

                                    int quantidade = 2;

                                    for(i=0; i<=100; i++)
                                    {

                                        if(i%2==0)
                                        {
                                            strcat(espaco,"Û");
                                        }
                                        system("CLS");//limpa a tela

                                        printf("\t\t\t\t\t\t\tImpressora \n\n");
                                        printf("\t\t\t               ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                                        printf("\n  Imprindo Arquivos      ");


                                        printf("\t\t  %s ",espaco);

                                        printf("\n\t\t\t               ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");

                                        printf("     %d%% ",i);
                                        printf("\n\n\n\n\n\n\n");

                                        if(i==0)
                                        {
        									printf("\t\t\t\t\t       LISTA DE ARQUIVOS SENDO IMPRESSOS\n\n\n");
                                            lista_da_imprime(&filaMA,&lista);

                                        }
                                    }
                                }
                                else
                                {
                                    printf("\n\nA fila est%c vazia, tente novamente.\n",160);
                                    sleep(2);
                                }
                                system("cls");
                            }
                            //MENU ANTERIOR
                            else if(escolha==2)
                            {
                                system("cls");
                            }

                        }
                        while(escolha!=2);
                    }

                    //VOLTAR PARA O MENU NORMAL
                    if(retorno_menu_alerta==6)
                    {
                        system("cls");
                        redistribuir(lista,&filaA,&filaB);
                        controle=6;
                    }
                    //SAIR DO PROGRAMA
                    if(retorno_menu_alerta==7)
                    {
                        retorno_menu_inicial=9;
                    }
                }
            }
            while(controle!=6 && retorno_menu_alerta !=7);
            if(controle==6)
            {
                menu_inicial();
                retorno_menu_inicial=escolha_do_menu_inicial();
                controle = 1;
                controle2=1;
            }

        }


        //SAIR
        if(retorno_menu_inicial==9)
        {
            int i =0;           ;
            char espaco[120]=""; //limpa o espaco reservado na memoria
            int tempo = clock();

            for(i=0; i<=100; i++)
            {
                if(i%2==0)
                {
                    strcat(espaco,"Û");
                }
                system("CLS");//limpa a tela
                printf("\t\t\t               ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                printf("\n       Saindo do Sistema");


                printf("\t\t  %s ",espaco);

                printf("\n\t\t\t               ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");

                printf("     %d%% ",i);
                printf("\n\n\n\n\n\n\n");
                Sleep(45);
            }

            system("cls");  //limpa a tela
            printf("Sistema deslogado.\n");

        }

    }
    while(retorno_menu_inicial!=9 && retorno_menu_inicial!=8);

    return 0;
}


//-------------------------------------------------------------FIM MAIN-----------------------------------------------------


void altera_numero_da_turma()
{

    int i=0,z=0,t=0,d,x,encontrou=0;

    char turma[100]; //variável de entrada
    int turmanovo; //Variável de entrada

    int tam; //Para ver o tamanho da palavra que foi inserida na entrada "turma", para posterior alocação na variável aux
    char* token; //Recebe o argumento que servirá de token para quebrar a string digitada na variável "turma"

    //Variáveis para ler do arquivo
    char nome_da_turma[100];
    int quantidade;
    int ano;

    //Variáveis auxiliares para quebra da turma digitada
    char* aux; //Cópia da turma para aux, ou seja turma = aux
    char aux2[100];
    char aux3[10];


    //Crição de arquivos
    FILE *alunos_por_turma;
    FILE *alunos_por_turma_aux;

    alunos_por_turma = fopen("Números de alunos por turma.txt","r");
    alunos_por_turma_aux = fopen("Novo números de alunos por turma.txt","w");
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

    x = atoi(aux3); //Converte o char armazenado na variável aux3 em inteiro


    while( (fscanf(alunos_por_turma,"%d %s %d\n", &ano, nome_da_turma, &quantidade))!=EOF ) //Lê o txt até encontrar o fim do arquivo
    {
        if(ano==x)
        {
            if(strcmp(nome_da_turma,aux2)==0)
            {
                for(i=0; i<strlen(nome_da_turma); i++)
                {
                    nome_da_turma[i]  = toupper(nome_da_turma[i]); // Converte caracter minusculo em maiusculo para aparecer para o usuário destacado
                }

                printf("\nO tamanho atual da turma %s %c: %d alunos!\n",nome_da_turma,130,quantidade);
                printf("\nQual o novo n%cmero de alunos dessa turma?\n",163);
                scanf("%d",&turmanovo);

                for(i=0; i<strlen(nome_da_turma); i++)
                {
                    nome_da_turma[i]  = tolower(nome_da_turma[i]); // Converte caracter maiusculo em minusculo para gravar no arquivo
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
        printf("A turma informada n%co se encontra no arquivo.\n",135);
    }
    else if(encontrou)
    {
        printf("Alterado com sucesso.\n");
    }

    fclose(alunos_por_turma);

    alunos_por_turma = fopen("Números de alunos por turma.txt","w");

    fclose(alunos_por_turma_aux);

    alunos_por_turma_aux = fopen("Novo números de alunos por turma.txt","r");


    while( (fscanf(alunos_por_turma_aux,"%d %s %d\n", &ano, nome_da_turma, &quantidade))!=EOF ) //L? o txt at? encontrar o fim do arquivo
    {
        fprintf(alunos_por_turma,"%d %s %d\n", ano,nome_da_turma,quantidade);
    }
    fclose(alunos_por_turma_aux);
    remove("Novo números de alunos por turma.txt"); //Remove o arquivo auxiliar
    fclose(alunos_por_turma);
}

int quantidade_de_alunos(char turma[]) //retorna a quantidade de alunos de uma turma, lendo no arquivo
{

    int i=0,j=0,tam;
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
        printf("N%co existe no arquivo.\n",198);
        return z;
    }
}

//Funções essenciais de Fila

void inicializa(Fila *f)
{
    f->fim=NULL;
    f->inicio=NULL;
}
int vazia(Fila *f)
{
    if(f->inicio==NULL)
        return 1; //se estiver vazia
    return 0; //se não estiver vazia
}

Celula* criar_no()
{
    Celula* q;
    q=(Celula*) malloc (sizeof(Celula));
    return q;
}

void insere_na_fila(Fila* a, Fila* b, char nome[],char turma[], int tempo)  //insere o elemento nas filas certas
{
    Celula* r;
    Celula* aux;
    Fila auxiliar;
    int soma_a=0, soma_b=0;

	inicializa(&auxiliar);
    r=criar_no();
    if(r!=NULL)
    {

        //inicializa outro no na fila da impressora
        strcpy(r->nome_elemento,nome);
        strcpy(r->nome_da_turma,turma);
        r->prioridade=tempo;
        r->prox=NULL;

        if(vazia(a)) //se a fila de a estiver vazia, insere em a
        {
            a->inicio=r;

            a->fim=r;
        }
        else if(vazia(b)) // se a fila de a não estiver vazia e a flia de b estiver, insere em b
        {
            b->inicio=r;

            b->fim=r;
        }
        else   // se nenhuma das filas estiver vazia

        {
            //calcula o tempo de espera de a e b
			aux=a->inicio;
            while(aux!=NULL)
            {
                soma_a+=aux->prioridade;
                enfileirar(&auxiliar,aux->nome_da_turma,aux->nome_elemento,aux->prioridade);
                desenfileirar(a);
                aux=aux->prox;
            }

            aux=auxiliar.inicio;
            while(aux!=NULL){

            	enfileirar(a,aux->nome_da_turma,aux->nome_elemento,aux->prioridade);
            	desenfileirar(&auxiliar);
            	aux=aux->prox;
			}

            aux=b->inicio;
            while(aux!=NULL)
            {
            	soma_b+=aux->prioridade;
            	enfileirar(&auxiliar,aux->nome_da_turma,aux->nome_elemento,aux->prioridade);
                desenfileirar(b);
                aux=aux->prox;
            }

            aux=auxiliar.inicio;
            while(aux!=NULL){
            	enfileirar(b,aux->nome_da_turma,aux->nome_elemento,aux->prioridade);
            	desenfileirar(&auxiliar);
            	aux=aux->prox;
			}


            // printf("soma a:%d soma b: %d\n",soma_a,soma_b);
            if(soma_a<=soma_b)
            {
                (a->fim)->prox=r;
                a->fim=r;

            }
            else
            {

                (b->fim)->prox=r;
                b->fim=r;
            }
        }

    }
    else
        printf("Erro na criacao do no\n");
}


void imprime (Fila* f, Fila *g)
{
    char c[100];
    char x[100];
    int w;
    int i;

    Celula* aux;
    if(vazia(f))
    {
        return;
    }
    else
    {
        aux=f->inicio;
    }
    printf("\t\t\t\t\t\t   - Arquivo: %s Turma: %s\n",aux->nome_elemento,aux->nome_da_turma);
    strcpy(c, aux->nome_da_turma);
    strcpy(x, aux->nome_elemento);
    w=aux->prioridade;
    enfileirar(g,c,x,w);
    desenfileirar(f);
    imprime(f,g);
}


void desenfileirar(Fila *fila)
{
    Celula *aux;
    char c[100];
    char b[100];

    if(vazia(fila)==1)
    {
       // printf("Fila esta vazia.\n");

    }
    aux = fila->inicio;
    strcpy(c, fila->inicio->nome_da_turma);
    strcpy(b, fila->inicio->nome_elemento);

    fila->inicio  = fila->inicio->prox; //o inicio recebe o proximo;



    if(fila->inicio==NULL) //fila ficou vazia;
    {
        fila->fim = NULL;
    }
    //printf("Removeu %s e %s.\n",c,b);
    free(aux);
}

void enfileirar(Fila* f, char turma[], char nome[],int tempo)
{
    Celula* q;
    q=criar_no();
    if(q!=NULL)  //se criou o no
    {
        strcpy(q->nome_da_turma,turma);
        strcpy(q->nome_elemento,nome);
        q->prioridade=tempo;
        q->prox=NULL;

        if(vazia(f))
        {
            f->inicio=q;
            f->fim=q;
        }
        else
        {
            (f->fim)->prox=q;
            f->fim=q;
        }
    }
    else
        printf("Erro ao criar o no");
}

int pesquisar_fila(Fila* fila,char nome[],char turma[])
{
    Celula* aux;
    Celula* lista;
    Celula* aux4;
    char c[100];
    char x[100];
    char* aux2;
    char* aux3;
    int w,tam=0,t=0;

    lista=NULL;// inicializa uma lista auxiliar

    //achando o elemento na fila
    if(vazia(fila)==0) //fila n vazia
    {

        aux=fila->inicio;// aux recebe o inicio da fila

        tam = strlen(nome);
        aux2 = (char*)malloc(tam * sizeof(char));
        strcpy(aux2,nome);

        tam = strlen(turma);
        aux3 = (char*)malloc(tam * sizeof(char));
        strcpy(aux3,turma);

        while(aux!=NULL)  //passa todos os elementos da fila para a lista
        {
            strcpy(c, aux->nome_da_turma);
            strcpy(x, aux->nome_elemento);
            w=aux->prioridade;
            insere_na_lista(&lista,x,c,w);
            aux=aux->prox;
        }



        t=remover_da_lista(&lista,aux2,aux3); //procura o elemento na lista e remove
        if(t==5)
        {
            return 1; //n achou o elemento
        }

        aux4=fila->inicio;

        while(aux4!=NULL)  //retira todos os elementos da fila
        {
            desenfileirar(fila);
            aux4=aux4->prox;
        }

        aux=lista;
        while(aux!=NULL)  //insere tudo que estava na lista para a fila
        {
            strcpy(c, aux->nome_da_turma);
            strcpy(x, aux->nome_elemento);
            w=aux->prioridade;
            enfileirar(fila,c,x,w);
            aux=aux->prox;
        }
    }
    else
    {
        printf("Elemento n%co encontrado.\n",198);
    }

}

int contar_elementos_fila(Fila *f, Fila *g)
{
    int cont=0;
    char c[100];
    char x[100];
    int w;


    Celula* aux;
    if(vazia(f))
    {
        printf("Erro -- Fila vazia\n");
    }
    else
    {
        aux=f->inicio;

        while(aux!=NULL)
        {
            strcpy(c, aux->nome_da_turma);
            strcpy(x, aux->nome_elemento);
            w=aux->prioridade;
            enfileirar(g,c,x,w);
            cont ++;
            desenfileirar(f);
            aux=aux->prox;
        }
    }
    return cont;
}

void lista_da_imprime(Fila *f,Celula** lista)
{

    char c[100];
    char x[100];
    int w;


    Celula* aux;
    int i=0;
    if(vazia(f))
    {
        printf("\t\t\t\t\t\tErro --  A Fila vazia\n");
        sleep(3);
        system("cls");
    }
    else
    {
        aux=f->inicio;
        while(aux!=NULL)
        {
            printf("\t\t\t\t\t        [%d] - Arquivo: %s Turma: %s\n",i+1,aux->nome_elemento,aux->nome_da_turma);

            strcpy(c, aux->nome_da_turma);
            strcpy(x, aux->nome_elemento);
            //w=aux->prioridade;
            remover_da_lista(lista,x,c);
            desenfileirar(f);
            aux=aux->prox;
            i++;
            sleep(1);
        }
    }
}

int escolha_de_imprimir()
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

            printf("\t\t  Op%c%co desejada: ",135,198);
            c=getch();
            printf("%c\n",c);

            if (isdigit(c)!=0)
            {
                digitado[i] = c;
                i++;
            }
            else if(c==8 && i)
            {
                digitado[i]='\0';
                i--;
                printf("\b \b");
            }
        }
        else
        {

            printf("\t\t  Digite uma op%c%co v%clida: ",135,198,160);
            c=getch();
            printf("%c\n",c);


            if (isdigit(c)!=0)
            {
                digitado[i] = c;
                i++;
            }
            else if(c==8 && i)
            {
                digitado[i]='\0';
                i--;
                printf("\b \b");
            }
        }
        cont ++;

    }
    while(c<'1' || c>'4');


    digitado[i]='\0';

    int tam = strlen(digitado);


    escolha = atoi(&digitado[tam-1]);

    return escolha;
}

void transferencia_lista_fila(Celula* lista, Fila* fila)
{
    Celula* aux;
    char c[100];
    char x[100];
    int w;


    aux=lista;
    while(aux!=NULL)
    {
        strcpy(c, aux->nome_da_turma);
        strcpy(x, aux->nome_elemento);
        w=aux->prioridade;
        enfileirar(fila,c,x,w);
        aux=aux->prox;
    }
}


void redistribuir(Celula* lista, Fila* a, Fila* b)
{
    Celula* aux;
    char c[100];
    char x[100];
    int w,tam=0,tempo;

    if(vazia(a)==0)  //se n estiver vazia
    {
        aux=a->inicio;
        while(aux!=NULL)    //remove todos os elementos da fila a
        {
            desenfileirar(a);
            aux=aux->prox;
        }
    }

    if(vazia(b)==0)  //se n estiver vazia
    {
        aux=b->inicio;
        while(aux!=NULL)    //remove todos os elementos da fila b
        {
            desenfileirar(b);
            aux=aux->prox;
        }
    }

    if(lista_vazia(lista))
    {
        printf("Erro -- lista vazia\n");
    }
    else
    {
        aux=lista;// aux recebe a lista


        while(aux!=NULL)  //passa todos os elementos da lista para as filas
        {
            strcpy(c, aux->nome_da_turma);
            strcpy(x, aux->nome_elemento);
            w=aux->prioridade;

            insere_na_fila(a,b,x,c,w);
            aux=aux->prox;
        }
    }
}

//FUNÇÕES PARA USO DA LISTA
int lista_vazia(Celula* lista)
{
    if(lista==NULL)//se estiver vazia
        return 1;
    else
        return 0;
}

void insere_na_lista(Celula** c,char nome[],char turma[], int tempo)
{
    Celula* q;
    Celula* aux;
    q=criar_no();

    if(q==NULL)
    {
        printf("Erro na aloca%cao do no",135);
        exit(1);
    }
    else
        strcpy(q->nome_elemento,nome);
    strcpy(q->nome_da_turma,turma);
    q->prioridade=tempo;
    q->prox=NULL;

    if(lista_vazia(*c)!=0) //se a lista esta vazia
    {
        *c=q;
    }
    else
    {
        aux=*c;
        while(aux->prox!=NULL)
        {
            aux=aux->prox;
        }
        aux->prox=q;
    }
}

void imprime_lista(Celula* lista)
{
    Celula *aux;
    int i=0;
    aux=lista;

	while(aux!= NULL)
    {
        printf("\t\t\t\t\t       [%d] - Arquivo: %s Turma: %s\n",i+1,aux->nome_elemento,aux->nome_da_turma);
        aux=aux->prox;
        i++;
    }
    printf("\n");
}

Celula* pesquisar_lista(Celula* lista, char nome[],char turma[])
{
    Celula* q;
    int tam=0,tam2=0;
    char *aux2;
    char *aux3;

    if(lista_vazia(lista)==0) //lista n ta vazia
    {
        q=lista;

        while(q!=NULL)
        {
            tam = strlen(q->nome_elemento);
            aux2 = (char*)malloc(tam * sizeof(char));
            strcpy(aux2,q->nome_elemento);

            tam2 = strlen(q->nome_da_turma);
            aux3 = (char*)malloc(tam2 * sizeof(char));
            strcpy(aux3,q->nome_da_turma);

            if(strcmp(aux2,nome)==0 && strcmp(aux3,turma)==0)
            {

                //printf("Elemento encontrado: %s e %s\n", q->nome_da_turma, q->nome_elemento);
                return q;
            }
            q=q->prox;
        }
    }
    else

        return NULL;
}


int remover_da_lista (Celula** lista, char nome[],char turma[])
{
    Celula* aux;
    Celula* q;
    aux=*lista;
    q=pesquisar_lista(*lista,nome,turma);

    if(q==NULL) //se nao achou o elemento
    {
        return 5;
    }

    else
    {
        if((*lista)==q)
        {

            if(lista_vazia(*lista)==0)  //n ta vazia
            {
                (*lista)= aux->prox;
                free(aux);
            }
            else
                printf("Erro ao remover\n");

        }
        else
        {
            while(aux->prox!=q)
            {
                aux=aux->prox;
            }
            aux->prox=q->prox;
            free(q);
        }
        return 1;
    }
}

int contar_elementos_da_lista(Celula *lista)
{
    int cont=0;
    Celula *aux;
    aux=lista;
    while(aux!= NULL)
    {
        cont ++;
        aux=aux->prox;
    }
    return cont;
}

int mover_pra_frente(Celula **lista)
{
    Celula *aux, *anterior;
    int maior;
    if(lista_vazia(*lista))
    {
        return 0;
    }
    aux = (*lista);
    maior=aux->prioridade;
    while(aux!=NULL)
    {
        if(aux->prioridade> maior)
        {
            anterior ->prox = aux->prox;
            aux ->prox = (*lista);
            (*lista) = aux;
        }
        anterior = aux;
        aux = aux->prox;
    }

    return 1;
}

void transferencia_fila_lista(Fila *fila, Fila* auxiliar, Celula** lista)
{
    Celula* aux;
    char c[100];
    char x[100];
    int w;

    aux=fila->inicio;

    while(aux!=NULL)  //percorre a fila nova
    {
        strcpy(c,aux->nome_elemento);
        strcpy(x,aux->nome_da_turma);
        w=aux->prioridade;
        insere_na_lista(&(*lista),c,x,w); //insere tudo na lista
        enfileirar(auxiliar,x,c,w); //coloca na auxiliar
        desenfileirar(fila);//retira da fila principal
        aux=aux->prox;
    }

    aux=auxiliar->inicio;
    while(aux!=NULL)  //retorna tudo para a principal e remove da auxiliar
    {
        enfileirar(fila,aux->nome_da_turma,aux->nome_elemento,aux->prioridade);
        desenfileirar(auxiliar);
        aux=aux->prox;
    }
}

int escolha_de_tamanho()
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

            printf("Quantos elementos ser%co adicionados na fila?\n",198);
            c=getch();
            printf("%c\n",c);

            if (isdigit(c)!=0)
            {
                digitado[i] = c;
                i++;
            }
            else if(c==8 && i)
            {
                digitado[i]='\0';
                i--;
                printf("\b \b");
            }
        }
        else
        {

            printf("\nDigite um tamanho v%clido: ",160);
            c=getch();
            printf("%c\n",c);


            if (isdigit(c)!=0)
            {
                digitado[i] = c;
                i++;
            }
            else if(c==8 && i)
            {
                digitado[i]='\0';
                i--;
                printf("\b \b");
            }
        }
        cont ++;

    }
    while(c<'1' || c>'4');


    digitado[i]='\0';

    int tam = strlen(digitado);


    escolha = atoi(&digitado[tam-1]);

    return escolha;

}

void menu_inicial()
{

    char dateStr[9];
    char timeStr[9];
    system("COLOR 0A");
    _strdate(dateStr);
    _strtime(timeStr);
    printf("\n\t FILA DE IMPRESS%cO ESCOLA ADIRON GON%cALVES BOAVENTURA \n",199,128);
    printf("\t\t  Hor%crio do sistema: %s\n",160,timeStr);
    printf("\t\t\t    ");
    system("date /t");
    printf("\n   --------------------------------------------------------------\n");
    printf("   |\t[1] - Adicionar elementos a fila de impress%co.          |\n",198);
    printf("   |\t[2] - Verificar fila de impress%co da impressora A.      |\n",198);
    printf("   |\t[3] - Verificar fila de impress%co da impressora B.      |\n",198);
    printf("   |\t[4] - Verificar toda fila de impress%co.                 |\n",198);
    printf("   |\t[5] - Remover algum elemento da fila de impress%co.      |\n",198);
    printf("   |\t[6] - Alterar n%cmero de alunos de uma turma.            |\n",163);
    printf("   |\t[7] - Imprimir                                          |\n");
    printf("   |\t[8] - Modo alerta.                                      |\n");
    printf("   |\t[9] - Sair.                                             |");
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

            printf("\t\t       Op%c%co desejada: ",135,198);
            c=getch();//captura o caractere digitado pelo usu?rio
            printf("%c\n",c);

            //isdigit verifica se o que foi digitado é um número ou não, retornando qualquer número diferente de 0, se for um número

            if (isdigit(c)!=0)  //se for um número
            {
                digitado[i] = c;//armazena no vetor de caracteres
                i++;
            }
            else if(c==8 && i)//se for pressionada a tecla BACKSPACE e houver caracteres já digitados, ou seja, i!=0
            {
                digitado[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
                i--;
                printf("\b \b");//o caractere digitado e apagado da tela, primeiro \b apaga o caracter da tela e o segundo \b tira o caracter da tela
            }
        }
        else
        {

            printf("\t\t       Digite uma op%c%co v%clida: ",135,198,160);
            c=getch();//captura o caractere digitado pelo usuário
            printf("%c\n",c);

            //isdigit verifica se o que foi digitado é um número ou não, retornando qualquer número diferente de 0, se for um número

            if (isdigit(c)!=0)  //se for um número
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
    while(c<'1' || c>'9');


    digitado[i]='\0';   //o índice atual do vetor de caracteres recebe a terminaçao da string

    int tam = strlen(digitado);

    //atoi converte char para int
    escolha = atoi(&digitado[tam-1]); //atoi() tem como um parâmetro um ponteiro para caracteres, por isso, pra usar com vetor tem que usar o &

    return escolha;
}

int escolha_menu_alerta()
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

            printf("\t\t       Op%c%co desejada: ",135,198);
            c=getch();//captura o caractere digitado pelo usu?rio
            printf("%c\n",c);

            //isdigit verifica se o que foi digitado é um número ou não, retornando qualquer número diferente de 0, se for um número

            if (isdigit(c)!=0)  //se for um número
            {
                digitado[i] = c;//armazena no vetor de caracteres
                i++;
            }
            else if(c==8 && i)//se for pressionada a tecla BACKSPACE e houver caracteres já digitados, ou seja, i!=0
            {
                digitado[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
                i--;
                printf("\b \b");//o caractere digitado e apagado da tela, primeiro \b apaga o caracter da tela e o segundo \b tira o caracter da tela
            }
        }
        else
        {

            printf("\t\t       Digite uma op%c%co v%clida: ",135,198,160);
            c=getch();//captura o caractere digitado pelo usuário
            printf("%c\n",c);

            //isdigit verifica se o que foi digitado é um número ou não, retornando qualquer número diferente de 0, se for um número

            if (isdigit(c)!=0)  //se for um número
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
    while(c<'1' || c>'7');


    digitado[i]='\0';   //o índice atual do vetor de caracteres recebe a terminaçao da string

    int tam = strlen(digitado);

    //atoi converte char para int
    escolha = atoi(&digitado[tam-1]); //atoi() tem como um parâmetro um ponteiro para caracteres, por isso, pra usar com vetor tem que usar o &

    return escolha;
}

int quantidade_de_folhas()
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

            printf("Quantidade de folhas: ");
            c=getch();
            printf("%c\n",c);

            if (isdigit(c)!=0)
            {
                digitado[i] = c;
                i++;
            }
            else if(c==8 && i)
            {
                digitado[i]='\0';
                i--;
                printf("\b \b");
            }
        }
        else
        {

            printf("\nDigite uma quantidade v%clida: ",160);
            c=getch();
            printf("%c\n",c);


            if (isdigit(c)!=0)
            {
                digitado[i] = c;
                i++;
            }
            else if(c==8 && i)
            {
                digitado[i]='\0';
                i--;
                printf("\b \b");
            }
        }
        cont ++;

    }
    while(c<'1' || isalpha(c));  //isalpha  ---- Verdadeiro se x é uma letra de A-Z ou a-z


    digitado[i]='\0';

    int tam = strlen(digitado);


    escolha = atoi(&digitado[tam-1]);

    return escolha;

}

void menu_modo_alerta()
{

    char dateStr[9];
    char timeStr[9];
    sleep(0);
    system("COLOR 0E");
    _strdate(dateStr);
    _strtime(timeStr);
    printf("\n\t FILA DE IMPRESS%cO ESCOLA ADIRON GON%cALVES BOAVENTURA \n",199,128);
    printf("\t\t  Hor%crio do sistema: %s\n",160,timeStr);
    printf("\t\t\t    ");
    system("date /t");
    printf("\n   --------------------------------------------------------------\n");
    printf("   |\t[1] - Adicionar elementos a fila de impress%co.          |\n",198);
    printf("   |\t[2] - Verificar toda fila de impress%co.                 |\n",198);
    printf("   |\t[3] - Remover algum elemento da fila de impress%co.      |\n",198);
    printf("   |\t[4] - Alterar n%cmero de alunos de uma turma.            |\n",163);
    printf("   |\t[5] - Imprimir                                          |\n");
    printf("   |\t[6] - Modo normal.                                      |\n");
    printf("   |\t[7] - Sair.                                             |");
    printf("\n   --------------------------------------------------------------\n");

}

