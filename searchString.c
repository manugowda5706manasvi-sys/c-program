#include <stdio.h>
#include <string.h>

/* Function Declarations */
void readString(char str[]);

void removeNewline(char str[]);

int getLength(char str[]);

int findPattern(char str[], char pat[], int start);

int replacePattern(char str[], char pat[], char rep[], char result[]);

void displayResult(int flag, char result[]);

int main() {
    char str[100],pat[100],rep[100],result[100];
    int flag;

    printf("Enter the string: ");
    readString(str);

    printf("Enter the pattern: ");
    readString(pat);

    printf("Enter the replacement: ");
    readString(rep);
    flag=replacePattern(str,pat,rep,result);
    displayResult(flag,result);


    return 0;
}

/* Function to read string */
void readString(char str[]) {
    fgets(str,100,stdin);
    removeNewline(str);

}

/* User-defined function to remove newline character */
void removeNewline(char str[]) {
    int i=0;
    while(str[i]!='\0'){
        if(str[i]=='\n'){
            str[i]='\0';
            break;
        }
        i++;
    }

}

/* Function to find string length */
int getLength(char str[]) {
    int len=0;
    while(str[len]!='\0'){
        len++;
    }
    return len;

}

/* Function to check pattern match */
int findPattern(char str[], char pat[], int start) {

    int i=0;
    while(pat[i]!='\0'){
        if(str[start+i]!=pat[i])
            return 0;
        i++;
        
    }
    return 1;
}

/* Function to replace pattern */
int replacePattern(char str[], char pat[], char rep[], char result[]) {
    int i=0,j=0,k=0;
    int patlen=getLength(pat);
    int replen=getLength(rep);
    int found=0;
    while(str[i]!='\0'){
        if(findPattern(str,pat,i)){
            found=1;
            for(k=0;k<replen;k++){
                result[j++]=rep[k];
            }
            i+=patlen;
        }
    }
    result[j]='\0';
    return found;

}

/* Function to display result */
void displayResult(int flag, char result[]) {

    if (flag==0) 
        printf("Pattern does not exist");
    else {
        printf("The main string after replacement is:\n");
        printf("%s",result);
}