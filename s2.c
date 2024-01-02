// 1.The game will begin with randomly between player 1 and player 2.
// 2.If a 6(six) is appeared then a chance is awarded to that player.
// 3.Snakes:- 99 to  1, 65 to 40, 25 to 9.
// 4.Ladder:- 70 to 93, 60 to 83, 13 to 42.
// 5.game will quit when you enter 'q'.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dice;
int extra_chance = 0;

int roll_dice() {
    return rand() % 6 + 1;
}

void display_chart(int curpos1, int curpos2, const char *player) {
    // system("clear");  // For Linux
    system("cls");  // For Windows

    int i, j;
    if(extra_chance==1){
        printf("You got a 6! Roll again for an extra chance.\n");
    }
    
    printf("%s rolls the dice and gets: %d\n", player, dice);

    for(i = 10; i >= 1; i--){
        for(j = 1; j <= 10; j++){
            int current_pos;
            if(i % 2 == 0)
                current_pos = (i - 1) * 10 + j;
            else
                current_pos = (i - 1) * 10 + 10 - j + 1;
            
            if (curpos1 == current_pos && curpos2 == current_pos)
                printf("*P1P2*\t");
            else if (curpos1 == current_pos)
                printf("*P1*\t");
            else if (curpos2 == current_pos)
                printf("*P2*\t");
            else
                printf("%d\t", current_pos);

            if (current_pos == 1)
                break;
        }
        printf("\n\n");
    }

    printf("--------------------------------------------------------------------------\n");
    printf("1. Snakes:- 25 to 9,\t 65 to 40,\t 99 to  1.\n2. Ladder:- 13 to 42,\t 60 to 83,\t 70 to 93.\n\n3. Game will quit when you enter 'q'.\n");
}

void snakes_ladders_cond(int *curpos){
    // Implementation of snakes and ladders logic
    if (*curpos == 99)
        *curpos = 1; // Snake at position 99
    else if (*curpos == 65)
        *curpos = 40; // Snake at position 65
    else if (*curpos == 25)
        *curpos = 9; // Snake at position 25
    else if (*curpos == 70)
        *curpos = 93; // Ladder at position 70
    else if (*curpos == 60)
        *curpos = 83; // Ladder at position 60
    else if (*curpos == 13)
        *curpos = 42; // Ladder at position 13
}

void player_turn(int *curpos1, int *curpos2, const char *player){
    extra_chance = 0;

    do{
        printf("%s's turn: Press Enter to roll the dice...", player);
        char ch = getchar(); // Wait for user input
        if(ch == 'q'){
            exit(0);
        }

        dice = roll_dice();
        printf("%s rolls the dice and gets: %d\n", player, dice);

        if(player[7] == '1'){
            *curpos1 += dice;
            snakes_ladders_cond(curpos1);
        }
        else{
            *curpos2 += dice;
            snakes_ladders_cond(curpos2);
        }

        if (*curpos1 >= 100 || *curpos2 >= 100) {
            printf("\n\n\t\t!!!!!!!!congratulation!!!!!!!!\n");
            printf("\t\t\t%s wins!\n\n\n", player);
            getchar();
            exit(0);
        }

        if(dice == 6){
            extra_chance = 1;
            printf("You got a 6! Roll again for an extra chance.\n");
        }
        else{
            extra_chance = 0;
        }

        display_chart(*curpos1, *curpos2, player);
    }while(extra_chance);
}

void main(){
    srand(time(NULL));

    printf("		** SNAKE AND LADDER GAME** \n");
	printf("Snakes:- 25 to 9,\t 65 to 40,\t 99 to  1.\nLadder:- 13 to 42,\t 60 to 83,\t 70 to 93.\n");
    printf("\n\t\tRULES\n-->Game will quit when you enter 'q'.\n");
    printf("-->The game will begin with randomly between player 1 and player 2.\n-->If a 6(six) is appeared then a chance is awarded to that player.\n\n\n");
    int curpos1 = 0, curpos2 = 0;
    int current_player = rand() % 2 + 1; // 1 for Player 1, 2 for Player 2

    while (1) {
        if (current_player == 1) {
            player_turn(&curpos1, &curpos2, "Player 1");
            current_player = 2;
        } else {
            player_turn(&curpos1, &curpos2, "Player 2");
            current_player = 1;
        }
    }
    printf("\n\n");
    getchar();
    
}
