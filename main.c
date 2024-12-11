/*          Compile and launch the maze (must be in main.c folder)

gcc main.c -o maze
maze

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


// Function to print a table in char format
void printTable(int *t, int n, boolean inChar)
{
    for(int i = 0; i<n;i++){
        for(int j = 0; j<n; j++){
            if(inChar){
                if (t[i*n+j]==0){
                    printf("%c", 178);
                }
                else if (t[i*n+j]==-1){
                    printf("%c", ' ');
                }
                else {
                    printf("%c", 177);
                }
            }
            else if (!inChar)
                printf("%i", t[i*n+j]);
        }
        printf("From %i to %i\n", i*n, i*n+n);
    }
}

// Setup the maze, each case with different numbers, separated with walls
void setup(int *t, int n)
{
    for (int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                if (i%2==0 || j%2==0)
                    t[i*n+j]=0;
                else
                    t[i*n+j]=i*n+j;
            }
    }
    // Set the beginning of the maze to 1
    t[n+1]=1; 

    // Start the random lib
    srand(time(NULL));
}

// Check if table contains only 0, 1 and -1 (walls, empty, fastest path)
int testTable(int *t, int n)
{
    for(int i=0; i<n*n; i++){
        if(t[i]!=0 && t[i]!=1 && t[i]!=-1){
            return 0;
        }
    }
    return 1;
}

// Creation of the maze
int creationLab(int *t, int n)
{
    int randomValue, randomValueB, temp;
    do{
        randomValue = rand()%(n*n+1);

        if (randomValue/n%2!=0 && randomValue%n%2!=0){
            if (t[randomValue]!=0){
                do{
                    randomValueB = rand()%4;
                    switch (randomValueB){
                        case 1 :if(t[randomValue]!=t[randomValue+2] && t[randomValue+2]!=0 && randomValue+2>0 && randomValue+2<n*n && (t[randomValue+2]==1 || 100<t[randomValue+2] || t[randomValue+2]<100+n+n)){
                                    for(int i = 0; i<n*n; i++){
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
                        case 2 : if(t[randomValue]!=t[randomValue-2] && t[randomValue-2]!=0 && randomValue-2>0 && randomValue-2<n*n && (t[randomValue-2]==1 || 100<t[randomValue-2] || t[randomValue-2]<100+n+n)){
                                    t[randomValue-1] = 1;
                                    for(int i = 0; i<n*n; i++){
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
                        case 3 : if(t[randomValue]!=t[randomValue+2*n] && t[randomValue+2*n]!=0  && randomValue+2*n>0 && randomValue+2*n<n*n && (t[randomValue+2*n]==1 || 100<t[randomValue+2*n]|| t[randomValue+2*n]<100+n+n)){
                                    t[randomValue+n] = 1;
                                    for(int i = 0; i<n*n; i++){
                                        if(t[i]==t[randomValue+2*n] || t[i]==t[randomValue]){
                                            if(t[randomValue+2*n]>t[randomValue]){
                                                t[i] = t[randomValue];
                                                t[randomValue+n] = t[randomValue];
                                            }
                                            else{
                                                t[i] = t[randomValue+2*n];
                                                t[randomValue+n] = t[randomValue];
                                            }
                                        }
                                    }
                                    temp = 1;
                                }
                                break;
                        case 4 : if(t[randomValue]!=t[randomValue-2*n] && t[randomValue-2*n]!=0 && randomValue-2*n>0 && randomValue-2*n<n*n && (t[randomValue-2*n]==1 || 100<t[randomValue-2*n] || t[randomValue-2*n]<100+n+n)){
                                    t[randomValue-n] = 1;
                                    for(int i = 0; i<n*n; i++){
                                        if(t[i]==t[randomValue-2*n] || t[i]==t[randomValue]){
                                            if(t[randomValue-2*n]>t[randomValue]){
                                                t[i] = t[randomValue];
                                                t[randomValue-n] = t[randomValue];
                                            }
                                            else{
                                                t[i] = t[randomValue-2*n];
                                                t[randomValue-n] = t[randomValue];
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
    }while(testTable(&t[0], n)==0);

    t[n]=1;
    t[n*n-1-n]=1;
}

// This function calculate the distance from the end of the maze to each case. 
// These calculations are stored in the tMove table. 
int calculateFastestPath(int *tMove, int n, int caseNumber)
{

    // Check if each nearby case is empty, then increment the right case by 1. 
    if(tMove[caseNumber + 1] < tMove[caseNumber] && tMove[caseNumber + 1] > 0){
        tMove[caseNumber] = -1;
        calculateFastestPath(tMove, n, caseNumber + 1);
    }
    else if(tMove[caseNumber - 1] < tMove[caseNumber] && tMove[caseNumber - 1] > 0){
        tMove[caseNumber] = -1;
        calculateFastestPath(tMove, n, caseNumber - 1);
    }
    else if(tMove[caseNumber + n] < tMove[caseNumber] && tMove[caseNumber + n] > 0){
        tMove[caseNumber] = -1;
        calculateFastestPath(tMove, n, caseNumber + n);
    }
    else if(tMove[caseNumber - n] < tMove[caseNumber] && tMove[caseNumber + 1] > 0){
        tMove[caseNumber] = -1;
        calculateFastestPath(tMove, n, caseNumber - n);
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
    int n;
    int point;

    // Maze initialization
    printf("\nHow much for the maze size ? ");
    scanf("%i", &n);
    if (n%2==0)
        n++;

    t = calloc(n*n, sizeof(int));
    tMove = calloc(n*n, sizeof(int));
    tResol = calloc(n*n, sizeof(int));

    setup(t, n);

    // Maze setup
    creationLab(&t[0], n);

    printTable(t, n, 1);

    // Maze resolution
    for (int i=0; i<n*n; i++){
        tMove[i] = t[i];
    }

    tMove[n * n - n - 1]=2;
    calculateReverseTable(tMove, n, n*n-1-n);

    for (int i=0; i<n*n; i++){
        tResol[i] = tMove[i];
    }

    printf("\nMaze : \n");
    calculateFastestPath(tMove, n, n);
    tMove[n*n-1-n] = -1;
    printTable(tMove, n, 1);

    free(tMove);
    free(t);
    free(tResol);
}
