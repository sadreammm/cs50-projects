#include <cs50.h>
#include <stdio.h>
#include <string.h>

int lengthNumber(long number);
void digitValidator(long ccNo);
bool cardValidator(long ccNo);

int main(){
    long ccNo = get_long("Number: ");
    bool checksum = cardValidator(ccNo);
    if(checksum){
        digitValidator(ccNo);
    }
    else{
        printf("INVALID\n");
    }
}

int lengthNumber(long number){
    int count=0;
    do{
        count++;
        number/=10;
    }while(number!=0);
    return count;
}
void digitValidator(long ccNo){
    int length = lengthNumber(ccNo);
    char tempccNo[30] = "";
    char cardType[30] = "";
    sprintf(tempccNo,"%ld",ccNo);

    switch(tempccNo[0]){
        case '3':
            if((length==15) && (tempccNo[1]=='4'||tempccNo[1]=='7')){
                    strcpy(cardType,"AMEX\n");
            }
            else{
                strcpy(cardType,"INVALID\n");
            }
            break;
        case '5':
            if((length==16) && (tempccNo[1]=='1'||tempccNo[1]=='2'||tempccNo[1]=='4'||tempccNo[1]=='4'||tempccNo[1]=='5')){
                    strcpy(cardType,"MASTERCARD\n");
            }
            else{
                strcpy(cardType,"INVALID\n");
            }
            break;
        case '4':
            if(length==13 || length == 16){
                    strcpy(cardType,"VISA\n");
            }
            else{
                strcpy(cardType,"INVALID\n");
            }
            break;
    }


    printf("%s",cardType);
}
bool cardValidator(long ccNo){
    int doubled = 0;
    int addOther = 0;
    int sum = 0;
    do{
        addOther+= ccNo%10;
        ccNo/=10;
        if(((ccNo%10) * 2)>9){
            doubled+=((ccNo%10) * 2)-9;
        }
        else{
            doubled+=(ccNo%10) * 2;
        }
        ccNo/=10;
    }while(ccNo!=0);
    sum = doubled + addOther;
    if(sum%10==0){
        return true;
    }
    return false;
}
