#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Usados para usar as funções srand e rand
#include "othello_func.h"

/*
###########################################################
# init_board - Esta função inicializa o tabuleiro (board)
#
# Argumentos:
# board - tabuleiro, caractér
# score - pontuação, inteiro
###########################################################
*/
void init_board(char board[][9], int score[2])
{
    int line, col, num = 49;

    for (line = 1; line < 9; line++)
    {
        for (col = 1; col < 9; col++)
        {
            board[line][col] = '.';  // Este loop tem a função de preencher o tabuleiro com '.' 
        }
    }

    for (line = 1; line < 9; line++)
    {
        board[line][0] = (char)num++;  //Este loop preenche a partir da linha 1 a 8, os números 1 a 8 por ordem crescente, usando a tabela de ascii
    }

    //No inicio do jogo estas peças são colocadas no centro do tabuleiro
    board[4][4] = 'o';
    board[5][5] = 'o';
    board[5][4] = 'x';
    board[4][5] = 'x';
    score[0] = 2;
    score[1] = 2;
}

/*
###########################################################
# print_board - Esta função mostra o tabuleiro no terminal
#
# Argumentos:
# board - tabuleiro, caractér
###########################################################
*/
void print_board(char board[][9])
{

    int line, col;

    printf("\n   A  B  C  D  E  F  G  H\n"); // Este printf indica as coordenadas do lado da coluna do tabuleiro.
    for (line = 0; line < 9; line++)
    {
        for (col = 0; col < 9; col++)
        {
            printf("%c  ", board[line][col]);  //Este loop tem a função de escrever no terminal o tabuleiro inteiro atravez da array board.
        }
        printf("\n");
    }
    printf("\n");
}

/*
###############################################################################################################
# verify - Esta função vai analisar todas as linas/colunas se existe jogadas possiveis
#
# Argumentos:
# board - tabuleiro, caractere
# color - peça do tabuleiro atual, caractere
# check - vetor que permite guardar se pode ser jogada numa certa direção, inteiro
# Valor de retorno:
# valid, inteiro
###############################################################################################################
*/
int verify(char board[][9], char color, int check[8])
{
    int valid = 1; // Inicializa-se com valid=1 para mostrar que no fim da análise de jogadas possíveis, se a analise demonstrar que não existe jogadas possiveis, retorna para a função game, 1, que obriga o game dar a vez à peça oposta. 
    for (int line = 1; line < 9; line++)
    {
        for (int col = 1; col < 9; col++) //Este loop vai indicar as diversas possibilidades de jogada.
        {
            if (flanked(board, line, col, color, check) == 0) //Esta função vai analisar as linhas e as colunas que são dadas pelo loop for.
            {
                valid = 0; // Se esta função flanked returnar 0, vai indicar ao programa que a linha e coluna que lhe foi atribuida é valida.
            }
        }
    }
    return valid;
}

/*
#########################################################################################################################
# next_move - Esta função permite cumprir as etapas pretendidas para efetuar a troca das peças para a peça do utilizador
#
# Argumentos:
# board - tabuleiro, caractere
# color - peça do tabuleiro atual, caractere
# check - vetor que permite guardar se pode ser jogada numa certa direção, inteiro
# score - pontuação, inteiro
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
#########################################################################################################################
*/
void next_move(char board[][9], char color, int check[8], int score[2], char player[2])
{
    int line, col;
    choose(&line, &col, color); //Esta função é usada para obter a linha e a coluna que o utilizador decidiu escolher.
    if (flanked(board, line, col, color, check) == 0) //O flanked vai analisar a linha e coluna escolhida pelo utilizador.
    {
        play(board, line, col, color, check, score, player); //Se o flanked retornar 0 significa que a linha e a coluna selecionada pelo utilizador é válida e possiblita a execução da função play para trocar as peças.
    }
    else
        wrong_play(board, color, check, score, player); //Se o flanked retornar 1 significa que a linha e a coluna selecionada pelo utilizador é inválida por consequente chama a função wrong_play para avisar ao utilizador fez uma jogada incorreta.
}

/*
##############################################################################################
# wrong_play - Esta função tem o propósito de avisar o utilizador que fez uma jogada invalida 
#
# Argumentos:
# board - tabuleiro, caractere
# color - peça do tabuleiro atual, caractere
# check - vetor que permite guardar se pode ser jogada numa certa direção, inteiro
# score - pontuação, inteiro
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
##############################################################################################
*/
void wrong_play(char board[][9], char color, int check[8], int score[2], char player[2])
{
    printf("\nInvalid Move!\n"); //Este printf avisa ao utilizador que fez uma jogada incorreta
    next_move(board, color, check, score, player); //Para remendar a jogada do utilizador, chama-se a função next_move para dar outra oportunidade ao utilizador fazer uma jogada diferente mas válida.
}

/*
#############################################################################################
# flanked - Esta função conta o número de peças viradas ao jogar numa certa linha e coluna. 
#
# Argumentos:
# board - tabuleiro, caractere
# line - linha, inteiro
# col - coluna, inteiro
# color - peça do tabuleiro atual, caractere
# check - vetor que permite guardar se pode ser jogada numa certa direção, inteiro
# Valor de retorno:
# binário (0/1), inteiro
##############################################################################################
*/
int flanked(char board[][9], int line, int col, char color, int check[8])
{
    int scan = 0, d_line = 0, d_col = 0, count = 0, n = 0;

    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++) //Este loop tem a função de analisar as diversas direções possiveis correspondentes a linha e coluna.
        {
            d_line = line + x; // Para não perder a linha original usamos a variável d_line para analisar as diversas direções correspondentes à variavel x (cima/baixo/nulo).
            d_col = col + y; // Para não perder a coluna original usamos a variável d_col para analisar as diversas direções correspondentes à variavel y (direita/esquerda/nulo).
            if (board[d_line][d_col] == color /*Se no inicio da análise as coordenadas da proxima linha e coluna tiverem a mesma peça, o check daquela direção é nula*/|| board[line][col] != '.' /*Se as coordenadas indicadas seja o utilizador ou computador, tiver uma peça nessas coordenadas o check de todas direções vai ter zero e posterior o flanked vai retornar 1 por ser uma jogada inválida*/|| d_line <= 0 || d_line >= 9 || d_col <= 0 || d_col >= 9 /* No inicio da analise, se as coordenadas da proxima linha/coluna excender as fronteiras do tabuleiro, o check daquela direção é nula*/)
            {
                check[n] = 0; //Se uma destas condições forem verdadeiras, o check dessa direção(n) passa a 0.
            }
            else
            {
                scan = 1; // Variável de controlo para controlar o loop da análise das diversas direções.
                while (scan != 0) //Enquando o loop tiver scan diferente de 0, ele vai analisar as diversas direções. 
                {

                    if (board[d_line][d_col] == '.' /* Se as coordenadas da proxima linha e coluna correspondem '.' termina o loop e o check daquela direção é nula. */ || d_line <= 0 || d_line >= 9 || d_col <= 0 || d_col >= 9 /* No inicio da analise, se as coordenadas da proxima linha/coluna excender as fronteiras do tabuleiro, o check daquela direção é nula*/)
                    {
                        check[n] = 0; //Se uma destas condições forem verdadeiras, o check dessa direção(n) passa a 0.
                        scan = 0; //Se uma destas condições forem verdadeiras, o scan passa para 0, por consequente termina o loop.
                    }

                    else if (board[d_line][d_col] == color /* Se as coordenadas da proxima linha e coluna correspondem a mesma peça termina o loop e o check daquela direção passa para 1. */)
                    {
                        check[n] = 1; //Se uma destas condições forem verdadeiras, o check dessa direção(n) passa a 1.
                        count++; //Se uma destas condições forem verdadeiras, o contador vai somar 1.
                        scan = 0; //Se uma destas condições forem verdadeiras, o scan passa para 0, por consequente termina o loop.
                    }
                    //Se as condições de cima não forem verdadeiras, vai voltar a analisar.
                    d_line += x; // Vai analisar a proxima linha correspondente à variavel x.  
                    d_col += y; // Vai analisar a proxima coluna correspondente à variavel y.
                }
            }
            n++; // Variavel de controlo que permite o vetor check alterar para a proxima direção. 
        }
    }
    //Este contador tem a função de verificar se a jogada feito pelo utilizador/computador é valida.
    if (count == 0)
        return 1; //Se o contador for igual a 0, ele retorna 1 que tem a função de indicar que a jogada que o utilizador/computador fez é invalida.
    else
        return 0; //Se o contador for igual ou superior a 1, ele retorna 0 que tem a função de indicar que a jogada que o utilizador/computador fez é valida.
}

/*
#########################################################################################################
# play - Esta função coloca uma peça de cor color na posição (line, col) e vira as peças do adversário 
#
# Argumentos:
# board - tabuleiro, caractere
# line - linha, inteiro
# col - coluna, inteiro
# color - peça do tabuleiro atual, caractere
# check - vetor que permite guardar se pode ser jogada numa certa direção, inteiro
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
##########################################################################################################
*/
void play(char board[][9], int line, int col, char color, int check[8], int score[2], char player[2])
{
    int d_line = 0, d_col = 0, sp = 0, n = 0;

    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++) //Este loop tem a função de analisar as diversas direções possiveis correspondentes a linha e coluna.
        {
            if (check[n] == 1) //Se a check de uma certa direção(n) for 1, ele efetua a troca das peças.
            {
                d_line = line + x; // Para não perder a linha original usamos a variável d_line para analisar as diversas direções correspondentes à variavel x (cima/baixo/nulo).
                d_col = col + y; // Para não perder a coluna original usamos a variável d_col para analisar as diversas direções correspondentes à variavel y (direita/esquerda/nulo).
                sp += count_flips_dir(board, line, col, x, y, color); // Antes de efectuar a troca das peças, a variável sp(score_player) vai contar quantas peças vão ser trocadas.  
                while (board[d_line][d_col] != color) //Este loop tem a função trocar as peças que não são correspondidas à peça atual. Se a proxima linha/coluna for igual à peça atual, termina o loop.
                {
                    board[d_line][d_col] = color; // A peça daquela linha e coluna correspondente à peça oposta em relação à peça atual, ele executa a troca das peças passando essa peça que era oposta à peça atual.
                    d_line += x; // Vai analisar a proxima linha correspondente à variavel x.
                    d_col += y; // Vai analisar a proxima coluna correspondente à variavel y.
                }
            }
            // Se o check daquela direção for nula(0), o check daquela direção troca para a outra direção.
            n++; // Variavel de controlo que permite o vetor check alterar para a proxima direção.
        }
    }

    board[line][col] = color; // As coordenadas indicadas pelo utilizador/computador trocam a peça oposta para a peça atual.
    score_game(color, sp, score, player); //Após a execução da troca de peças, é chamada esta função com o objetivo de atualizar a pontuação de ambos os jogadores.
}

/*
##########################################################################################################################
# count_flips_dir - Esta função conta quantas peças serão viradas, numa certa linha e coluna, e numa certa numa direção 
#
# Argumentos:
# board - tabuleiro, caractere
# line - linha, inteiro
# col - coluna, inteiro
# delta_line - direção da linha, inteiro
# delta_col - direção da coluna, inteiro
# color - peça do tabuleiro atual, caractere
# Valor de retorno:
# count, inteiro
##########################################################################################################################
*/
int count_flips_dir(char board[][9], int line, int col, int delta_line, int delta_col, char color)
{
    int count = 0;
    line = line + delta_line; // Nesta linha usamos à variavel delta_line para atualizar a linha numa certa direção (cima/baixo/nulo).
    col = col + delta_col; // Nesta linha usamos à variavel delta_col para atualizar a coluna numa certa direção (direita/esquerda/nulo).
    while (board[line][col] != color) // Este loop tem a função de analisar a linha e a coluna a peça oposta em relação a peça atual e contar essas peças, pois a posteriori a peça oposta é trocada para a peça atual.  
    {
        count++; // Este contador tem a função contar o nº peças que vão ser trocadas para a peça atual.
        line += delta_line; // Nesta linha usamos à variavel delta_line para atualizar a linha numa certa direção (cima/baixo/nulo).
        col += delta_col; // Nesta linha usamos à variavel delta_col para atualizar a coluna numa certa direção (direita/esquerda/nulo).
    }
    return count; // Depois de ser feito o loop, a função retorna o count (nº peças que serão viradas para as peças originais).
}

/*
##############################################################################
# score_game - Esta função atualiza a pontuação dos jogadores 
#
# Argumentos:
# color - peça do tabuleiro atual, caractere
# score_player - nº peças viradas, inteiro
# score - pontuação, inteiro
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
##############################################################################
*/
void score_game(char color, int score_player, int score[2], char player[2])
{
    if (color == player[0]) // Se a peça for correspondente ao utilizador, adiciona a pontuação ao utilizador e retira a pontuação(ou nº peças) do computador. 
    {
        score[0] += score_player + 1; // A pontuação do utilizador é atualizada com a soma do score_player (nº peças que foram viradas) + 1 (corresponde a coordenada original introduzida pelo utilizador).
        score[1] = (score[1] - score_player); // A pontuação do computador é atualizada com a subtração do score_player (nº peças que foram viradas para a peça atual). 
    }
    else // Se a peça for correspondente ao computador, adiciona a pontuação ao computador e retira a pontuação(ou nº peças) do utilizador.
    {
        score[1] += score_player + 1; // A pontuação do computador é atualizada com a soma do score_player (nº peças que foram viradas) + 1 (corresponde a coordenada original introduzida pelo computador).
        score[0] = (score[0] - score_player); // A pontuação do utilizador é atualizada com a subtração do score_player (nº peças que foram viradas para a peça atual). 
    }
}

/*
##############################################################################
# display_score - Esta função exibe a pontuação dos jogadores 
#
# Argumentos:
# score - pontuação, inteiro
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
##############################################################################
*/
void display_score(int score[2], char player[2])
{
    if (player[0] == 'x') // Se as peças do utilizador forem iguais as pretas, vai exibir o resultado final da pontuação (nº peças), correspondentes a cada um dos jogadores.
        printf("Black: %d discs, White: %d discs\n", score[0], score[1]); // Este printf vai exibir o resultado com o utilizador com as peças pretas e ao computador com as peças brancas.
    else // Se as peças do utilizador forem iguais as brancas, vai exibir o resultado final da pontuação (nº peças), correspondentes a cada um dos jogadores.
        printf("Black: %d discs, White: %d discs\n", score[1], score[0]); // Este printf vai exibir o resultado com o computador com as peças pretas e ao utilizador com as peças brancas.
}

/*
###################################################################################
# choose - Esta função pergunta ao utilizador qual é a jogada que pretende fazer 
#
# Argumentos:
# *line - linha, inteiro
# *col - coluna, inteiro
# color - peça do tabuleiro atual, caractere
###################################################################################
*/
void choose(int *line, int *col, char color)
{
    char cs = 0; // cs(col_source) - variavel que vai guardar o caractere (letra) e converte-la para o número da coluna que corresponde a coluna do caractere. 
    printf("(%c) choose your move. For instance: 5F\n", color); // Este printf pede ao utilizador introduzir as coordenadas para efectuar a sua jogada.
    scanf("%d%c", line, &cs); // O scanf guarda as coordenadas introduzidas pelo utilizador e associa-las nas respetivas variavéis.
    *col = (int)cs - 64; // Nesta linha ocorre a conversão de caractere(letra) para inteiro(número). Faz -64 para poder corresponder o inteiro à coluna corresponte a letra onde o utilizador introduziu. 
}

/*
#####################################################################
# ra - Esta função escolhe aleatoriamente a peça para o utilizador 
#
# Valor de retorno:
# ('x' ou 'o'), caractere
#####################################################################
*/
char ra()
{
    //rand() - retorna um número pseudo-aleatório no intervalo de [0, RAND_MAX]. RAND_MAX - é uma constante integral cujo valor é o valor máximo retornado pela função rand.
    int n = rand() % 2; // Nesta linha procede a escolha aleatoria entre números binários(0,1).
    if (n == 0) // Se a variavel n (número) for 0, as peças do utilizador são correspondidas às peças pretas.
    {
        printf("\nYour discs are Black\n"); // Informa ao utilizador quais são as peças que lhe pertencem.
        return 'x'; // Esta função vai retornar o caractere 'x' ao utilizador.
    }
    else // Se a variavel n (número) for 1, as peças do utilizador são correspondidas às peças brancas.
    {
        printf("\nYour discs are White\n"); // Informa ao utilizador quais são as peças que lhe pertencem.
        return 'o'; // Esta função vai retornar o caractere 'o' ao utilizador.
    }
}

/*
#################################################################################################
# computer_play - Esta função permite o computador pensar na melhor jogada possivel e efetua-la 
#
# Argumentos:
# board - tabuleiro, caractere
# color - peça do tabuleiro atual, caractere
# check - vetor que permite guardar se pode ser jogada numa certa direção, inteiro
# score - pontuação, inteiro
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
#################################################################################################
*/
void computer_play(char board[][9], char color, int check[8], int score[2], char player[2])
{
    int b_l, b_c, sc, bs = 1, n = 0; // bs(best_score) = 1, para chegar esta função, teve que ser analisada antes para verificar se o computador tem jogadas possiveis, e como esta função é chamada porque existe jogadas válidas, o bs é colocado 1 como standard que existe jogadas possiveis.  
    char letter;
    for (int line = 1; line < 9; line++)
    {
        for (int col = 1; col < 9; col++) //Este loop vai indicar as diversas possibilidades de jogada.
        {
            if (flanked(board, line, col, color, check) == 0) //Esta função vai analisar as linhas e as colunas que são dadas pelo loop for.
            {
                sc = 0;
                for (int x = -1; x < 2; x++)
                {
                    for (int y = -1; y < 2; y++)  //Este loop tem a função de analisar as diversas direções possiveis correspondentes a linha e coluna.
                    {
                        if (check[n] == 1) // Se a check de uma certa direção(n) for 1, ele efetua a contagem daquela direção.
                        {
                            sc += count_flips_dir(board, line, col, x, y, color); // Nesta linha é chamada a função count_flip_dir para contar quantas peças serão viradas e esse número é guardado na variável sc(score_computer). 
                        }
                        n++; // Variavel de controlo que permite o vetor check alterar para a proxima direção.
                    }
                }
                if (bs <= sc) // Nesta linha é usado o bs(best_score) e o sc(score_computer). Se a variavel sc for igual ou superior à variavel bs, ele guarda a linha e coluna correspondentes à variavel sc, pois quando maior for o sc, melhor vai ser a jogada do computador. 
                {
                    b_l = line; // b_l (best_line). Nesta linha o b_l guarda a linha corespondente ao maior número de sc. 
                    b_c = col; // b_c (best_col). Nesta linha o b_c guarda a coluna corespondente ao maior número de sc.
                    bs = sc; // Nesta linha o bs(best_score) é atualizado com o maior nº de sc(score_computer).
                }
            }
        }
    }
    flanked(board, b_l, b_c, color, check); //Esta função vai analisar as linhas e as colunas que são dadas b_l (best_line) e b_c (best_col) e vai atualizar o vetor check.
    play(board, b_l, b_c, color, check, score, player); //Após da utilização do flanked, é usada a função play para trocar as peças para as peças predefenidas pelo computador e a postriori é feito a atualização da pontuação (nºpeças).
    letter = (char)b_c + 64; // É convertido a coluna selecionado pelo computador para caracter para exibir ao utilizador quais as coordenadas que o computador selecionou.
    printf("\nMy move: %d%c\n\n", b_l, letter); // Ocorre a exibição da seleção de coordenadas escolhidas pelo computador.
}

/*
#################################################################################
# winner - Esta função exibe o vencedor/perdedor do jogo
#
# score - pontuação, inteiro
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
################################################################################
*/
void winner(int score[2], char player[2])
{
    printf("Game Over\n"); // É exibido ao utilizador que o jogo chegou ao fim.
    display_score(score, player); // É exibido a pontuação dos dois jogadores (utilizador/computador).

    if (score[0] > score[1]) // Se a pontuação do utilizador for superior à pontuação do computador, é exibido uma mensagem de vitoria para o utilizador
        printf("You win!\n");

    else if (score[0] == score[1]) // Se a pontuação do utilizador for igual à pontuação do computador, é exibido uma mensagem de empate para o utilizador
        printf("It's a draw!\n");

    else // Se a pontuação do utilizador for inferior à pontuação do computador, é exibido uma mensagem de derrota para o utilizador
        printf("You lose!\n");

    printf("\n");
    printf("© Miguel Costa | Rodrigo Marques | Universidade de Évora | 2022\n"); // Autores do projeto "Othello Game"
}

/*
########################################################################################
# load_game - Esta função lê o ficheiro "jogadas.txt" e executa as jogadas 
#
# Argumentos:
# argc - verifica se no terminal se existe alguma leitura do ficheiro, inteiro
# *argv[] - nome do ficheiro, caractere
# *f - ponteiro de ficheiros, FILE
# board - tabuleiro, caractere
# color - peça do tabuleiro atual, caractere
# check - vetor que permite guardar se pode ser jogada numa certa direção, inteiro
# score - pontuação, inteiro
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
# Valor de retorno:
# ('x' ou 'o'), caractere
########################################################################################
*/
char load_game(int argc, char *argv[], FILE *f, char color, char board[][9], int check[8], int score[2], char player[2])
{
    char c;
    int line = 0, col = 0, count = 1; // Count = 1, corresponde ao caractere 'x'. 

    if (argc > 1) // Na execução do código, nos argumentos da função main (argc) se for superior a 1 significa que está a ser executado o ficheiro indicado pelo utilizador. 
    {
        f = fopen(argv[1], "r"); // É aberto o ficheiro indicado pelo utilizador, no modo de leitura.
        if (f == NULL) // Se o ficheiro não tiver jogadas, é transmitido uma mensagem ao utilizador que o ficheiro não abriu com sucesso ou não tem dados.
        {
            printf("Could not open file\n");
        }
        else // Se o ficheiro tiver jogadas é executado desta maneira:
        {
            while (!feof(f)) // Enquando o ficheiro não chegar ao fim do texto é efetuado estas etapas...
            {
                if (count % 2 == 0) // Se o resto do valor do contador for 0, a cor da peça passa para branco.
                    color = 'o';
                else // Se o resto do valor do contador for 1, a cor da peça passa para preto.
                    color = 'x';
                fscanf(f, "%d%c", &line, &c); // Em cada linha do ficheiro é lido as coordenadas das jogadas. 
                col = (int)c - 64; // Nesta linha ocorre a conversão de caractere(letra) para inteiro(número). Faz -64 para poder corresponder o inteiro à coluna corresponte a letra onde o utilizador introduziu.
                if (flanked(board, line, col, color, check) == 0) //O flanked vai analisar a linha e coluna escolhida pelo utilizador.
                {
                    play(board, line, col, color, check, score, player); // Se o flanked retornar 0 significa que a linha e a coluna guardada no ficheiro é válida e possiblita a execução da função play para trocar as peças.
                    count++; // count é uma variavel de controlo que permite efectuar a troca a vez de jogada.
                }
                else // Se o flanked retornar 1 significa que a linha e a coluna guardada no ficheiro é inválida,por consequente encerra este loop.
                {
                    break;
                }
            }
        }
        fclose(f); // É fechado o ficheiro indicado pelo utilizador.
    }
    if (count % 2 == 0) // Se o resto do valor do contador for 0, a função retorna a cor para branco ('o').
        return 'o';
    else
        return 'x'; // Se o resto do valor do contador for 1, a função retorna a cor para preto ('x').
}

/*
##################################################################################################################
# save_player - Esta função guarda a peça atual na memória do jogador, e coloca a peça oposta no computador  
#
# Argumentos:
# color - peça do tabuleiro atual, caractere
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
##################################################################################################################
*/
void save_player(char color, char player[2])
{
    // player[0] - Utilizador | player[1] - Computador
    if (color == 'x') // Se a cor escolhida pela função ra é preta, o utilizador passa ser o jogador a possuir a cor preta e o computador a possuir a cor branca.
    {
        player[0] = 'x';
        player[1] = 'o';
    }
    else // Se a cor escolhida pela função ra é branca, o utilizador passa ser o jogador a possuir a cor branca e o computador a possuir a cor preta.
    {
        player[1] = 'x';
        player[0] = 'o';
    }
}

/*
########################################################################################
# game - Esta função executa o procedimento do jogo 
#
# Argumentos:
# board - tabuleiro, caractere
# check - vetor que permite guardar se pode ser jogada numa certa direção, inteiro
# color - peça do tabuleiro atual, caractere
# score - pontuação, inteiro
# player - vetor que guarda as peças correspondentes ao jogador/computador, caractere
########################################################################################
*/
void game(char board[][9], int check[8], char color, int score[2], char player[2])
{
    int end_of_match = 0, skip_turn = 0;
    while (end_of_match == 0) // Enquando o end_of_match for igual a 0, procede o jogo. Se o end_of_match for igual a 1, terminha o loop e encerra o codigo.
    {
        if (color == player[1]) // Se a cor da peça corresponde à peça do computador é efetuado o procedimento das jogadas do computador.
        {
            if (verify(board, color, check) == 1) // Se a função verify verifica que o computador não tem jogadas possiveis ocorrem as seguintes etapas...
            {
                if (skip_turn == 1) // Se o skip_turn ainda estiver a 1, significa que ambas as peças não tem jogadas possiveis, concluindo que preencheram o tabuleiro inteiro.
                {
                    end_of_match = 1; // É indicado que o jogo chegou ao fim.
                    print_board(board); // É exibido o tabuleiro final ao utilizador.
                    winner(score, player);  // É exibido o resultado do jogo.
                    continue; // Vai voltar para o while no entanto como o end_of_match = 1 vai terminar o loop.
                }
                skip_turn = 1; // O computador perde a vez de jogar.
                color = player[0]; // A peça é trocada para a peça do utilizador.
                continue; // Vai voltar repetir o while no entanto vai proceder as etapas de jogada do utilizador.
            }
            else // Se a função verify verifica que o computador tem jogadas possiveis ocorrem as seguintes etapas...
            {
                if (skip_turn == 1) // Se na vez do utilizador não existia jogadas possiveis, é exibido uma mensagem que o utilizador perdeu a vez de jogar.
                {
                    printf("\nYou missed the turn!\n");
                }
                skip_turn = 0; // Ele apaga a variavel de controlo passando para 0.
                computer_play(board, color, check, score, player); // Procede a realização das jogadas do computador.
                color = player[0]; // A peça é trocada para a peça do utilizador.
            }
        }
        else  // Se a cor da peça corresponde à peça do utilizador é efetuado o procedimento das jogadas do utilizador.
        {
            if (verify(board, color, check) == 1) // Se a função verify verifica que o utilizador não tem jogadas possiveis ocorrem as seguintes etapas...
            {
                if (skip_turn == 1) // Se o skip_turn ainda estiver a 1, significa que ambas as peças não tem jogadas possiveis, concluindo que preencheram o tabuleiro inteiro.
                {
                    end_of_match = 1; // É indicado que o jogo chegou ao fim.
                    print_board(board); // É exibido o tabuleiro final ao utilizador.
                    winner(score, player); // É exibido o resultado do jogo.
                    continue; // Vai voltar para o while no entanto como o end_of_match = 1 vai terminar o loop.
                }
                skip_turn = 1; // O utilizador perde a vez de jogar.
                color = player[1]; // A peça é trocada para a peça do computador.
                continue; // Vai voltar repetir o while no entanto vai proceder as etapas de jogada do computador.
            }
            else // Se a função verify verifica que o utilizador tem jogadas possiveis ocorrem as seguintes etapas...
            {
                if (skip_turn == 1) // Se na vez do computador não existia jogadas possiveis, é exibido uma mensagem que o computador perdeu a vez de jogar.
                {
                    printf("\nThe computer lost its turn to play!\n");
                }
                skip_turn = 0; // Ele apaga a variavel de controlo passando para 0.
                print_board(board); // É exibido o estado atual do tabuleiro ao utilizador.
                next_move(board, color, check, score, player); // Procede a realização das jogadas do utilizador.
                print_board(board); //É exibido o estado atual do tabuleiro ao utilizador após a jogada efetuada.
                color = player[1]; // A peça é trocada para a peça do computador.
            }
        }
    }
}