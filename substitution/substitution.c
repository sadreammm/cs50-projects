#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool keyValidator(string key);
void encrypt(string plaintext, string key);

int main(int argc,string argv[]){
    if(argc!=2){
        printf("1 command line key required\n");
        return 1;
    }
    if(keyValidator(argv[1])){
        printf("Invalid key\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    encrypt(plaintext, argv[1]);
}

bool keyValidator(string key){
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
    if(length==26 && count==length && !rep){
        return false;
    }
    return true;
}

void encrypt(string plaintext, string key){
    char ciphertext[1000] = "";
    string compare = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0,n=strlen(plaintext); i<n; i++){
        if(isalpha(plaintext[i])){
            for(int j=0,l=strlen(key); j<l; j++){
                if(toupper(plaintext[i])==compare[j]){
                    if (isupper(plaintext[i])) {
                        char letter[2] = {toupper(key[j]), '\0'}; // Convert char to string
                        strcat(ciphertext, letter);
                    } else {
                        char letter[2] = {tolower(key[j]), '\0'}; // Convert char to string
                        strcat(ciphertext, letter);
                    }
                }
            }
        }
        else{
            char letter[2] = {plaintext[i], '\0'}; // Convert char to string
            strcat(ciphertext, letter);
        }
    }
    printf("ciphertext: %s\n",ciphertext);
}
