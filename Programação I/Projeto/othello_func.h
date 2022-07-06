void init_board(char board[][9], int score[2]);

void print_board(char board[][9]);

int verify(char board[][9], char color, int check[8]);

void next_move(char board[][9], char color, int check[8], int score[2], char player[2]);

void wrong_play(char board[][9], char color, int check[8], int score[2], char player[2]);

int flanked(char board[][9], int line, int col, char color, int check[8]);

void play(char board[][9], int line, int col, char color, int check[8], int score[2], char player[2]);

int count_flips_dir(char board[][9], int line, int col, int delta_line, int delta_col, char color);

void score_game(char color, int score_player, int score[2], char player[2]);

void display_score(int score[2], char player[2]);

void choose(int *d_line, int *d_col, char color);

char ra();

void computer_play(char board[][9], char color, int check[8], int score[2], char player[2]);

void winner(int score[2], char player[2]);

char load_game(int argc, char *argv[], FILE *f, char color, char board[][9], int check[8], int score[2], char player[2]);

void save_player(char color, char player[2]);

void game(char board[][9], int check[8], char color, int score[2], char player[2]);