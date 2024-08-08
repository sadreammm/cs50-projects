#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int letterCount(string text, int length);
int wordCount(string text, int length);
int sentenceCount(string text, int length);

int main(){
    string text = get_string("Text: ");
    int length = strlen(text);

    int letters = letterCount(text,length);
    int words = wordCount(text,length);
    int sentences = sentenceCount(text,length);

    double L = (letters/(double)words)*100;
    double S = (sentences/(double)words)*100;
    double index = 0.0588 * L - 0.296 * S - 15.8;

    int X = round(index);

    if(X>16){
        printf("Grade 16+\n");
    }
    else if(X<1){
        printf("Before Grade 1\n");
    }
    else{
        printf("Grade %i\n",X);
    }
    return 0;
}

int letterCount(string text, int length){
    int count = 0;
    for(int i=0; i<length; i++){
        if(isalpha(text[i])){
            count++;
        }
    }
    return count;
}
int wordCount(string text, int length){
    int count=1;
    for(int i=0; i<length; i++){
        if(text[i]==' '){
            count++;
        }
    }
    return count;
}
int sentenceCount(string text, int length){
    int count=0;
    for(int i=0; i<length; i++){
        if(text[i]=='.'|| text[i]=='!' || text[i]=='?'){
            count++;
        }
    }
    return count;
}
