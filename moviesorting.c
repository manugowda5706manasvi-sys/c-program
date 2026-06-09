#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[100];
    char language[50];
    int year;
    float rating;
} Movie;

/* Function Prototypes */

int countMovies(char filename[]);
Movie* allocateMemory(int count);
void readMovies(char filename[], Movie *movies, int count);
void displayMoviesFromFile(char filename[], int n);
void sortMovies(Movie *movies, int count);
void writeMovies(char filename[], Movie *movies, int count);
void freeMemory(Movie **movies);

/* Main Function */

int main()
{

    printf("Enter how many movie records to display: ");
    
    if(n > count)
    {
        n = count;
    }
    printf("\nBefore Sorting:\n\n");
  
    printf("\nAfter Sorting:\n\n");

    printf("\nSorted movie data stored successfully.\n");

    return 0;
}

/* Function Definitions */

int countMovies(char filename[])
{
    FILE *fp;
    char line[200];
    int lines=0;
    fp=fopen(filename,"r");

   
    if(fp==NULL)
    {
        printf("File cannot be opened\n");
        exit(1);
    }
    while(fgets(line,sizeof(line),fp)!=NULL){
        lines++;
    }
    return lines-1;

}

Movie* allocateMemory(int count)
{
    Movie *movies;
    movies=(Movie*)malloc(count*sizeof(Movie));

    if(movies==NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);

    }
    return movies;
}

void readMovies(char filename[], Movie *movies, int count)
{
    FILE *fp;
    char header[200];
    int i=0;
    fp=fopen(filename,"r");

    if(fp==NULL)
    {
        printf("File cannot be opened\n");
        exit(1);
    }
    fgets(header,sizeof(header),fp);
    for(i=0;i<count;i++){
        fscanf(fp,"%99[^,],%49[^,],%d,%f",movies[i].name,movies[i].language,movies[i].year,movies[i].rating);

    }
    fclose(fp);
    
}

void displayMoviesFromFile(char filename[], int n)
{
    FILE *fp;
    int i;
    Movie movies;

    if()
    {
        printf("File cannot be opened\n");

    }

    {
        
        printf("%s | %s | %d | %.1f\n", );
    }

}

void sortMovies(Movie *movies, int count)
{

}

void writeMovies(char filename[], Movie *movies, int count)
{
    if()
    {
        printf("Cannot create output file\n");
    }
    fprintf(fp, "Movie Name,Language,Year,Rating\n");
    
        fprintf( , "%s,%s,%d,%.1f\n", );
    }

}

void freeMemory(Movie **movies)
{

}