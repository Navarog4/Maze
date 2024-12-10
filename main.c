/*          Compile and launch the program (must be in the "main.c" folder)

gcc main.c -o maze
maze

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Function to print a table in char format
void printTable(int *t, int nbBord, boolean inChar)
{
    for(int i = 0; i<nbBord;i++){
        for(int j = 0; j<nbBord; j++){
            if(inChar){
                if (t[i*nbBord+j]==0){
                    printf("%c", 178);
                }
                else if (t[i*nbBord+j]==-1){
                    printf("%c", ' ');
                }
                else {
                    printf("%c", 177);
                }
            }
            else if (!inChar)
                printf("%i", t[i*nbBord+j]);
        }
        printf("From %i to %i\n", i*nbBord, i*nbBord+nbBord);
    }
}

// Setup random table
void setupRandomTable(int *t, int nbBord)
{
    // Set random cases table, with walls in between
    for (int i = 0; i<nbBord; i++){
            for(int j = 0; j<nbBord; j++){
                t[i*nbBord+j]=i*nbBord+j;
                if (i%2==0 || j%2==0)
                    t[i*nbBord+j]=0;
            }
    }

    printTable(t, nbBord, 0);

    // Set the beginning of the maze to 1
    t[nbBord+1]=1; 

    // Start the random lib
    srand(time(NULL));
}

// Check if table contains only 0 and 1 (walls and empty)
int testTable(int *t, int nbBord)
{
    for(int i=0; i<nbBord*nbBord; i++){
        if(t[i]!=0 && t[i]!=1){
            return 0;
        }
    }
    return 1;
}

// Creation of the maze
int creationLab(int *t, int nbBord)
{
    int randomValue, randomValueB, temp;
    do{
        randomValue = rand()%(nbBord*nbBord+1);

        if (randomValue/nbBord%2!=0 && randomValue%nbBord%2!=0){
            if (t[randomValue]!=0){
                do{
                    randomValueB = rand()%4;
                    switch (randomValueB){
                        case 1 :if(t[randomValue]!=t[randomValue+2] && t[randomValue+2]!=0 && randomValue+2>0 && randomValue+2<nbBord*nbBord && (t[randomValue+2]==1 || 100<t[randomValue+2] || t[randomValue+2]<100+nbBord+nbBord)){
                                    for(int i = 0; i<nbBord*nbBord; i++){
                                        if(t[i]==t[randomValue+2] || t[i]==t[randomValue]){
                                            if(t[randomValue+2]>t[randomValue]){
                                                t[i] = t[randomValue];
                                                t[randomValue+1] = t[randomValue];
                                            }
                                            else{
                                                t[i] = t[randomValue+2];
                                                t[randomValue+1] = t[randomValue];
                                            }
                                        }
                                    }
                                    temp = 1;
                                }
                                break;
                        case 2 : if(t[randomValue]!=t[randomValue-2] && t[randomValue-2]!=0 && randomValue-2>0 && randomValue-2<nbBord*nbBord && (t[randomValue-2]==1 || 100<t[randomValue-2] || t[randomValue-2]<100+nbBord+nbBord)){
                                    t[randomValue-1] = 1;
                                    for(int i = 0; i<nbBord*nbBord; i++){
                                        if(t[i]==t[randomValue-2] || t[i]==t[randomValue]){
                                            if(t[randomValue-2]>t[randomValue]){
                                                t[i] = t[randomValue];
                                                t[randomValue-1] = t[randomValue];
                                            }
                                            else{
                                                t[i] = t[randomValue-2];
                                                t[randomValue-1] = t[randomValue];
                                            }
                                        }
                                    }
                                    temp = 1;
                                }
                                break;
                        case 3 : if(t[randomValue]!=t[randomValue+2*nbBord] && t[randomValue+2*nbBord]!=0  && randomValue+2*nbBord>0 && randomValue+2*nbBord<nbBord*nbBord && (t[randomValue+2*nbBord]==1 || 100<t[randomValue+2*nbBord]|| t[randomValue+2*nbBord]<100+nbBord+nbBord)){
                                    t[randomValue+nbBord] = 1;
                                    for(int i = 0; i<nbBord*nbBord; i++){
                                        if(t[i]==t[randomValue+2*nbBord] || t[i]==t[randomValue]){
                                            if(t[randomValue+2*nbBord]>t[randomValue]){
                                                t[i] = t[randomValue];
                                                t[randomValue+nbBord] = t[randomValue];
                                            }
                                            else{
                                                t[i] = t[randomValue+2*nbBord];
                                                t[randomValue+nbBord] = t[randomValue];
                                            }
                                        }
                                    }
                                    temp = 1;
                                }
                                break;
                        case 4 : if(t[randomValue]!=t[randomValue-2*nbBord] && t[randomValue-2*nbBord]!=0 && randomValue-2*nbBord>0 && randomValue-2*nbBord<nbBord*nbBord && (t[randomValue-2*nbBord]==1 || 100<t[randomValue-2*nbBord] || t[randomValue-2*nbBord]<100+nbBord+nbBord)){
                                    t[randomValue-nbBord] = 1;
                                    for(int i = 0; i<nbBord*nbBord; i++){
                                        if(t[i]==t[randomValue-2*nbBord] || t[i]==t[randomValue]){
                                            if(t[randomValue-2*nbBord]>t[randomValue]){
                                                t[i] = t[randomValue];
                                                t[randomValue-nbBord] = t[randomValue];
                                            }
                                            else{
                                                t[i] = t[randomValue-2*nbBord];
                                                t[randomValue-nbBord] = t[randomValue];
                                            }
                                        }
                                    }
                                    temp = 1;
                                }
                                break;
                        default :
                                break;
                    }
                }while(temp==0);
            }
        }
    }while(testTable(&t[0], nbBord)==0);

    t[nbBord]=1;
    t[nbBord*nbBord-1-nbBord]=1;
}

// This function calculate the distance from the end of the maze to each case. 
// These calculations are stored in the tMove table. 
int calculateFastestPath(int *tMove, int nbBord, int caseNumber)
{

    // Check if each nearby case is empty, then increment the right case by 1. 
    if(tMove[caseNumber + 1] < tMove[caseNumber] && tMove[caseNumber + 1] > 0){
        tMove[caseNumber] = -1;
        calculateFastestPath(tMove, nbBord, caseNumber + 1);
    }
    else if(tMove[caseNumber - 1] < tMove[caseNumber] && tMove[caseNumber - 1] > 0){
        tMove[caseNumber] = -1;
        calculateFastestPath(tMove, nbBord, caseNumber - 1);
    }
    else if(tMove[caseNumber + nbBord] < tMove[caseNumber] && tMove[caseNumber + nbBord] > 0){
        tMove[caseNumber] = -1;
        calculateFastestPath(tMove, nbBord, caseNumber + nbBord);
    }
    else if(tMove[caseNumber - nbBord] < tMove[caseNumber] && tMove[caseNumber + 1] > 0){
        tMove[caseNumber] = -1;
        calculateFastestPath(tMove, nbBord, caseNumber - nbBord);
    }
}


int calculateReverseTable(int *tMove, int nbBord, int caseNumber)
{
    // Check if each nearby case is empty, then increment the right case by 1. 
    if(tMove[caseNumber + 1] > tMove[caseNumber] || tMove[caseNumber + 1] == 1){
        tMove[caseNumber + 1] = tMove[caseNumber] + 1;
        calculateReverseTable(tMove, nbBord, caseNumber + 1);
    }
    if(tMove[caseNumber - 1] > tMove[caseNumber] || tMove[caseNumber - 1] == 1){
        tMove[caseNumber - 1] = tMove[caseNumber] + 1;
        calculateReverseTable(tMove, nbBord, caseNumber - 1);
    }
    if(tMove[caseNumber + nbBord] > tMove[caseNumber] || tMove[caseNumber + nbBord] == 1){
        tMove[caseNumber + nbBord] = tMove[caseNumber] + 1;
        calculateReverseTable(tMove, nbBord, caseNumber + nbBord);
    }
    if(tMove[caseNumber - nbBord] > tMove[caseNumber] || tMove[caseNumber - nbBord] == 1){
        tMove[caseNumber - nbBord] = tMove[caseNumber] + 1;
        calculateReverseTable(tMove, nbBord, caseNumber - nbBord);
    }
}

int main(void)
{
    int *t = NULL, *tMove = NULL, *tResol = NULL, pointPos;
    int nbBord;
    int point;

    // Maze initialization
    printf("\nHow much for the maze size ? ");
    scanf("%i", &nbBord);
    if (nbBord%2==0)
        nbBord++;

    t = calloc(nbBord*nbBord, sizeof(int));
    tMove = calloc(nbBord*nbBord, sizeof(int));
    tResol = calloc(nbBord*nbBord, sizeof(int));

    setupBlankTable(&t[0], nbBord);

    // Maze setup
    creationLab(&t[0], nbBord);

    printTable(t, nbBord, 1);

    // Maze resolution
    for (int i=0; i<nbBord*nbBord; i++){
        tMove[i] = t[i];
    }

    tMove[nbBord * nbBord - nbBord - 1]=2;
    calculateReverseTable(tMove, nbBord, nbBord*nbBord-1-nbBord);

    for (int i=0; i<nbBord*nbBord; i++){
        tResol[i] = tMove[i];
    }

    printf("\nLe labyrinthe est : \n\n");
    calculateFastestPath(tMove, nbBord, nbBord);
    tMove[nbBord*nbBord-1-nbBord] = -1;
    printTable(tMove, nbBord, 1);

    free(tMove);
    free(t);
    free(tResol);
}
