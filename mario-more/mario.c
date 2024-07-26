#include <stdio.h>
#include <cs50.h>

int main(){
    int height;
    int spaces;
    //get vaid input from user
    do{
        height = get_int("Height: ");
    }while(!(height>0 && height<=8));

    for(int i=1; i<=height; i++){
        spaces = height - i;
        //print spaces
        for(int j=spaces; j>0;j--){
            printf(" ");
        }
        //left pyramid
        for(int k=0;k<i;k++){
            printf("#");
        }
        //2 space gap
        printf("  ");
        //right pyramid
        for(int l=0;l<i;l++){
            printf("#");
        }
        printf("\n");
    }
}
