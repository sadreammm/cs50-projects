#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int calScore(string word);

int main(){
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int score1 = calScore(player1);
    int score2 = calScore(player2);

    printf("%i\n",score1);
    printf("%i\n",score2);

    if(score1>score2){
        printf("Player 1 wins!/n");
    }
    else if(score2>score1){
        printf("Player 2 wins!/n");
    }
    else{
        printf("Tie!/n");
    }
    return 0;
}

int calScore(string word){
    int charPoint[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1,	8, 5, 1, 3,	1, 1, 3, 10, 1,	1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;
    for(int i=0, n=strlen(word); i<n; i++){
        char temp = toupper(word[i]);
        if(isupper(temp)){
            score+=charPoint[temp-65];
        }
    }
    return score;
}
