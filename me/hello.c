#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
    string key = get_string("key: ");
    int count=0;
    int length = strlen(key);
    bool rep = false;
    for(int i=0; i<length; i++){
        if(isalpha(key[i])){
            count++;
        }
    }
    for(int i=0; i<length-1; i++){
        for(int j=i+1; j<length; j++){
            if(key[i]==key[j+1]){
                rep=true;
                break;
            }
        }
    }
    printf("%i %i %i\n",length,count,rep);
    if(length==26 && count==length && !rep){
        printf("hi\n");
        return true;
    }

}
