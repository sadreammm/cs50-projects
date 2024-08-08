#include <cs50.h>
#include <stdio.h>

int main(){
    int change;
    int coins = 0;

    do{
        change = get_int("Change owed: ");
    }while(change<0);

    int quarters = change/25;
    change%=25;
    coins +=quarters;

    int dimes = change/10;
    change%=10;
    coins+=dimes;

    int nickels = change/5;
    change%=5;
    coins+=nickels;

    int pennies = change/1;
    change%=1;
    coins+=pennies;

    printf("%i\n",coins);
}
