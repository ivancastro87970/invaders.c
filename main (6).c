#include <stdio.h>

#include <stdlib.h>

#include <conio.h>

#include <windows.h>

#include <locale.h>



#define DIREITA 77

#define ESQUERDA 75

#define SAIR 27





int menu(int opcao);

int menuDificuldade(int dificuldade);

int menuArma(int tiroJogador);

void ecraInicial();

void guardaProgresso(int pontuacao);

void guardaPontuacao(int pontuacao);

void mostraPontuacao();





int main()

{

    int col = 25;

    int lin = 40;

    int x;

    int y;

    int yi;

    char matriz[col][lin];

    char jogador = 38;

    char alien = 64;

    char escudoAlien = 'O';

    char tiroAlien = 248;

    char explosao = 35;

    int pontuacao = 0;

    int vitoria = 1;

    int tiro = 1;

    int alienPronto = 0;

    char keyPress;

    int velAlien;

    int velAlienFinal;





    srand(time(NULL));

    setlocale(LC_ALL, "Portuguese");



    //Chamada da funçao menu

    int opcao;

    opcao = menu(opcao);



    switch (opcao)

    {

    case 1:

        system("cls");



        //Chamada da Função Menu da Dificuldade

        int dificuldade;

        dificuldade = menuDificuldade(dificuldade);



        system("cls");





        //Chamada da Função Menu da Arma

        int tiroJogador;

        tiroJogador = menuArma(tiroJogador);





        system("cls");





        //Chamada da Função Ecrã Inicial

        ecraInicial();







        /*Construção da Matriz*/



        int totalAliens = 0;



        for (x = 0; x < lin; x++) {

            for (y = 0; y < col; y++) {



                if ((y + 1) % 2 == 0 && y < 7 && x > 4 && x < lin - 5 && x % 2 == 0) {

                    matriz[y][x] = alien;

                    totalAliens++;

                }



                else if ((y + 1) % 2 == 0 && y >= 7 && y < 9 && x > 4 && x < lin - 5 && x % 2 == 0) {

                    matriz[y][x] = escudoAlien;

                    totalAliens = totalAliens + 2;

                }



                else {

                    matriz[y][x] = ' ';

                }

            }

        }



        matriz[col - 1][lin / 2] = jogador;

        int i = 1;

        char direcao = 'l';

        int atuaisAliens = totalAliens;

        while (atuaisAliens > 0 && vitoria) {

            int drop = 0;

            velAlien = 1 + 10 * atuaisAliens / totalAliens;

            tiro++;





            if (dificuldade == 1) {

                velAlienFinal = velAlien * 2;

            }



            if (dificuldade == 2) {

                velAlienFinal = velAlien * 1.5;

            }



            if (dificuldade == 3) {

                velAlienFinal = velAlien;

            }





            /*Imprimir no Ecrã*/



            system("cls");

            printf("   PONTUAÇÃO:  %d   DIFICULDADE:  NIVEL %d", pontuacao, dificuldade);

            printf("\n");



            for (y = 0; y < col; y++) {

                printf("|");



                for (x = 0; x < lin; x++) {

                    printf("%c", matriz[y][x]);

                }

                printf("|");

                printf("\n");

            }





            /*Timing do Tiro*/



            for (x = 0; x < lin; x++) {



                for (y = col - 1; y >= 0; y--) {



                    if (i % 2 == 0 && matriz[y][x] == tiroAlien && (matriz[y + 1][x] != alien & matriz[y + 1][x] != escudoAlien)) {

                        matriz[y + 1][x] = tiroAlien;

                        matriz[y][x] = ' ';

                    }



                    else if (i % 2 == 0 && matriz[y][x] == tiroAlien && (matriz[y + 1][x] == alien | matriz[y + 1][x] == escudoAlien)) {

                        matriz[y][x] = ' ';

                    }

                }

            }

            for (x = 0; x < lin; x++) {



                for (y = 0; y < col; y++) {



                    if ((i % 5) == 0 && (matriz[y][x] == escudoAlien | matriz[y][x] == alien) && (rand() % 15) > 13 && matriz[y + 1][x] != tiroJogador) {



                        for (yi = y + 1; yi < col; yi++) {



                            if (matriz[yi][x] == alien

                                | matriz[yi][x] == escudoAlien) {

                                alienPronto = 0;

                                break;

                            }

                            alienPronto = 1;

                        }



                        if (alienPronto) {

                            matriz[y + 1][x] = tiroAlien;

                        }

                    }



                    if (matriz[y][x] == tiroJogador && matriz[y - 1][x] == alien) {

                        matriz[y][x] = ' ';

                        matriz[y - 1][x] = explosao;

                        atuaisAliens--;

                        pontuacao = pontuacao + 10;

                    }



                    else if (matriz[y][x] == tiroJogador && matriz[y - 1][x] == escudoAlien) {

                        matriz[y][x] = ' ';

                        matriz[y - 1][x] = alien;

                        atuaisAliens--;

                        pontuacao = pontuacao + 10;

                    }



                    else if (matriz[y][x] == tiroJogador && matriz[y - 1][x] == tiroAlien) {

                        matriz[y][x] = ' ';

                    }



                    else if (matriz[y][x] == explosao) {

                        matriz[y][x] = ' ';

                    }



                    else if ((i + 1) % 2 == 0 && matriz[y][x] == tiroAlien && matriz[y + 1][x] == jogador) {

                        matriz[y + 1][x] = explosao;

                        matriz[y][x] = ' ';

                        vitoria = 0;

                    }



                    else if (matriz[y][x] == tiroJogador && matriz[y - 1][x] != tiroAlien) {

                        matriz[y][x] = ' ';

                        matriz[y - 1][x] = tiroJogador;

                    }

                }

            }





            /*Direção dos Aliens*/



            for (y = 0; y < col; y++) {

                if (matriz[y][0] == alien) {

                    direcao = 'r';

                    drop = 1;

                    break;

                }

                if (matriz[y][lin - 1] == alien) {

                    direcao = 'l';

                    drop = 1;

                    break;

                }

            }





            /*update board*/



            if (i % velAlienFinal == 0) {



                if (direcao == 'l') {



                    for (x = 0; x < lin - 1; x++) {



                        for (y = 0; y < col; y++) {



                            if (drop && (matriz[y - 1][x + 1] == alien || matriz[y - 1][x + 1] == escudoAlien)) {

                                matriz[y][x] = matriz[y - 1][x + 1];

                                matriz[y - 1][x + 1] = ' ';

                            }



                            else if (!drop && (matriz[y][x + 1] == alien || matriz[y][x + 1] == escudoAlien)) {

                                matriz[y][x] = matriz[y][x + 1];

                                matriz[y][x + 1] = ' ';

                            }

                        }

                    }

                }

                else {



                    for (x = lin; x > 0; x--) {



                        for (y = 0; y < col; y++) {



                            if (drop && (matriz[y - 1][x - 1] == alien || matriz[y - 1][x - 1] == escudoAlien)) {

                                matriz[y][x] = matriz[y - 1][x - 1];

                                matriz[y - 1][x - 1] = ' ';

                            }



                            else if (!drop && (matriz[y][x - 1] == alien || matriz[y][x - 1] == escudoAlien)) {

                                matriz[y][x] = matriz[y][x - 1];

                                matriz[y][x - 1] = ' ';

                            }

                        }

                    }

                }



                for (x = 0; x < lin; x++) {



                    if (matriz[col - 1][x] == alien) {

                        vitoria = 0;

                    }

                }

            }





            /*Controlar o Jogador*/



            if (kbhit()) {

                keyPress = getch();

            }



            else {

                keyPress = ' ';

            }



            if (keyPress == ESQUERDA) {



                for (x = 0; x < lin; x = x + 1) {



                    if (matriz[col - 1][x + 1] == jogador) {

                        matriz[col - 1][x] = jogador;

                        matriz[col - 1][x + 1] = ' ';

                    }

                }

            }



            if (keyPress == DIREITA) {



                for (x = lin - 1; x > 0; x = x - 1) {



                    if (matriz[col - 1][x - 1] == jogador) {

                        matriz[col - 1][x] = jogador;

                        matriz[col - 1][x - 1] = ' ';

                    }

                }

            }



            if (keyPress == 'w' && tiro > 2) {



                for (x = 0; x < lin; x = x + 1) {



                    if (matriz[col - 1][x] == jogador) {

                        matriz[col - 2][x] = tiroJogador;

                        tiro = 0;

                    }

                }

            }

            i++;



            if (keyPress == SAIR) {



                //Chamada da Funçao para Guardar o Progresso do Jogo num Ficheiro após tecla SAIR

                guardaProgresso(pontuacao);

            }



            Sleep(50); //Taxa de Atualização do Jogo (50ms)





        }

        system("cls");

        printf("     PONTUAÇÃO:    %d", pontuacao);

        printf("\n");

        for (y = 0; y < col; y++) {

            printf("|");

            for (x = 0; x < lin; x++) {

                printf("%c", matriz[y][x]);

            }

            printf("|");

            printf("\n");

        }

        Sleep(1000);

        system("cls");



        if (vitoria != 0) {

            printf("\n \n \n \n \n \n                                        PARABÉNS! \n \n \n \n \n");

            Sleep(1000);

            printf("\n \n                                                    PONTUAÇÃO: %d", pontuacao);

            Sleep(1000);

            int bonus = totalAliens * 20 - i;

            printf("\n \n                                                      Bonus: %d", bonus);

            Sleep(1000);

            printf("\n \n                                                   Total PONTUAÇÃO: %d", pontuacao + bonus);

            printf("\n \n \n \n                                                 MUITO BEM");

            Sleep(1000);

            printf(", HEROI.");

            Sleep(1000);

            getch();

        }



        else {

            printf("\n \n \n \n \n \n                                          MISSÃO FRACASSADA :( ");

            Sleep(1000);

            printf("\n \n \n \n \n \n                                         OS ALIENS DESTRUIRAM TE!");

            Sleep(1000);

            printf("\n \n \n \n \n \n                                           PONTUCAO FINAL: %d", pontuacao);

            getch();





            //Chamada da função para Guardar a Pontuação num Ficheiro

            guardaPontuacao(pontuacao);



        }

        break;





    case 2:

        system("cls");

        break;



    case 3:

        system("cls");



        //Chamada da função que mostra a pontuação

        mostraPontuacao();

        break;



    default:

        printf("Opção inválida!");

        break;

    }

}











//Função Menu



int menu(int opcao)

{

    printf("\n \n                                             Selecione uma opção: \n \n \n");

    Sleep(1000);

    printf("                                             Novo jogo: 1\n \n \n");

    Sleep(1000);

    printf("                                            Carregar jogo: 2\n \n \n");

    Sleep(1000);

    printf("                                          Ver placar de Pontuações: 3\n \n \n");

    Sleep(1000);

    scanf("%d", &opcao);

    return opcao;

}





//Funcao Menu da Dificuldade



int menuDificuldade(int dificuldade)

{

    printf("\n \n                                     Selecione a sua dificuldade: \n \n \n");

    Sleep(1000);

    printf("                                          Fácil: 1\n \n \n");

    Sleep(1000);

    printf("                                          Médio: 2\n \n \n");

    Sleep(1000);

    printf("                                          Difícil: 3\n \n \n");

    Sleep(1000);

    scanf("%d", &dificuldade);



    return dificuldade;

}





//Função Menu da Arma



int menuArma(int tiroJogador)

{

    printf("\n \n                                        Selecione a sua arma: \n \n \n");

    Sleep(1000);

    printf("                                           Arma Devastadora: 1\n \n \n");

    Sleep(1000);

    printf("                                            Arma Suprema: 2\n \n \n");

    Sleep(1000);

    printf("                                            Arma Galática: 3\n \n \n");

    Sleep(1000);

    scanf("%d", &tiroJogador);



    if (tiroJogador == 1) {

        tiroJogador = 43;

    }



    if (tiroJogador == 2) {

        tiroJogador = 42;

    }



    if (tiroJogador == 3) {

        tiroJogador = 34;

    }



    return tiroJogador;

}





//Função Ecrã Inicial



void ecraInicial()

{

    printf("\n \n                                     BEM VINDO COMANDANTE, ESTAVÁMOS À SUA ESPERA! \n \n \n \n");

    Sleep(1000);

    printf("                                       CHEGOU A HORA DE DERROTAR OS INIMIGOS! \n \n \n \n");

    Sleep(1000);

    printf("                                                    BOA SORTE!!! \n \n \n \n");

    Sleep(1000);

    printf("\n \n \n \n                                      PRESSIONE QUALQUER TECLA PARA INICIAR");

    getch();

}





//Funçao para Guardar o Progresso do Jogo num Ficheiro após tecla SAIR



void guardaProgresso(int pontuacao)

{

    FILE* file;

    file = fopen("GuardaPontuacao.txt", "a");



    if (file == NULL) {

        printf("Ficheiro não encontrado");

        exit(0);

    }



    fprintf(file, "%d ", pontuacao);



    fclose(file);



    /*           FILE *file2;

                   file2 = fopen("GuardaProgresso.txt", "w");



                    if(file2 == NULL) {

                   printf("Ficheiro não encontrado");

                   exit(0);

                   }



                    fprintf(file2, "%c", matriz[col][lin]);

                   fclose(file2);  */



    system("cls");

    system("PAUSE");





    exit(0);

}



//Função para Guardar a Pontuação num Ficheiro



void guardaPontuacao(int pontuacao)

{



    FILE* file;

    file = fopen("GuardaPontuacao.txt", "a");



    if (file == NULL) {

        printf("Ficheiro não encontrado");

        exit(0);

    }



    fprintf(file, "\n%d", pontuacao);





    fclose(file);



}





//Função que mostra a Pontuação         



void mostraPontuacao()

{

    FILE* file;

    file = fopen("GuardaPontuacao.txt", "r");



    if (file == NULL) {

        printf("Ficheiro não encontrado");

        exit(0);

    }



    char frase[900];

    while (fgets(frase, 900, file) != NULL) {

        printf("%s", frase);

    }



    fclose(file);

}