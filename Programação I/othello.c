#include <stdio.h>
#include <stdlib.h>
#include "othello_func.h"
#include <time.h> //Usados para usar as funções srand e rand

int main(int argc, char *argv[])
{
    FILE *f; // É uma variavel local chamada f (do tipo FILE) que tem a função mais tarde de abrir o ficheiro "jogadas.txt" e manipular esse ficheiro.
    char board[9][9], color, player[2]; // Declaração do tabuleiro; da cor da peça;  um vetor que guarda a cor da peça e corresponde um certo jogador.
    int check[9], score[2]; // Declaração do vetor check (guarda a direção de uma jogada expecifica, 8 - significa 8 diferemtes direções, sejam diagonais, horizontais ou verticais.) Declaração do vetor score (guarda a pontuação (nº peças) dos jogadores).
    init_board(board, score); // Esta função inicializa o tabuleiro (board)
    printf("\nOthello Game\n"); // Exibe no inicio o titulo do jogo.
    srand(time(NULL)); // Esta função é um gerador de números aleatórios com o número fornecido.
    color = ra(); // É efetuado a escolha da cor para o utilizador.
    save_player(color, player); // É guardado a peça escolhida ao utilizador e guardar a peça oposta ,em relação ao utilizaodor, do computador.
    color = load_game(argc, argv, f, color, board, check, score, player); // Vai verificar se existe algum ficheiro e executa-la.
    game(board, check, color, score, player); // Após da execução do ficheiro o programa vai executar os procedimentos do jogo.
}