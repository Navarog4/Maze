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
                else if (t[i*nbBord+j]==1){
                    printf("%c", 177);
                }
                else if (t[i*nbBord+j]==-1){
                    printf("%c", ' ');
                }
                else {

                }
            }
            else if (!inChar)
                printf("%i", t[i*nbBord+j]);
        }
        printf("From %i to %i\n", i*nbBord, i*nbBord+nbBord);
    }
}

// Setup blank table
void setupBlankTable(int *t, int nbBord)
{
    // Set blank table, with walls
    for (int i = 0; i<nbBord; i++){
            for(int j = 0; j<nbBord; j++){
                t[i*nbBord+j]=(i*nbBord+j)+100;
                if (i%2==0 || j%2==0)
                    t[i*nbBord+j]=0;
            }
    }

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

int creationLab(int *t, int nbBord) /////V�rification : OK
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
int calculateReverseTable(int *tMove, int nbBord, int caseNumber)
{
    // Check if each nearby case is empty, then increment the right case by 1. 
    if(tMove[caseNumber + 1] == 1){
        tMove[caseNumber + 1] = tMove[caseNumber] + 1;
        calculateReverseTable(tMove, nbBord, caseNumber + 1);
    }
    else if(tMove[caseNumber - 1] == 1){
        tMove[caseNumber - 1] = tMove[caseNumber] + 1;
        calculateReverseTable(tMove, nbBord, caseNumber - 1);
    }
    else if(tMove[caseNumber + nbBord] == 1){
        tMove[caseNumber + nbBord] = tMove[caseNumber] + 1;
        calculateReverseTable(tMove, nbBord, caseNumber + nbBord);
    }
    else if(tMove[caseNumber - nbBord] == 1){
        tMove[caseNumber - nbBord] = tMove[caseNumber] + 1;
        calculateReverseTable(tMove, nbBord, caseNumber - nbBord);
    }
}


void randomResolTab(int *tResol, int nbBord, int origine, int randomN, int randomBegin){
    int tempVal = tResol[origine];
    int tempCase = origine;

    tResol[tempCase]=-1;
    if(randomN != randomBegin){
        if(randomN == -1)
            randomN = randomBegin;

        tResol[tempCase]=-1;
        if(randomN == 1){
            if(tResol[tempCase+1]<tempVal && tResol[tempCase+1]!=0 && tResol[tempCase+1]!=-1){
                tempVal=tResol[tempCase+1];
                tResol[tempCase]=-1;
                tempCase++;
            }
            else{
                randomResolTab(tResol, nbBord, origine, (randomN + 1)%4, randomBegin);
            }
        }
        else if (randomN == 2){
            if(tResol[tempCase-1]<tempVal && tResol[tempCase-1]!=0 && tResol[tempCase-1]!=-1){
                tempVal=tResol[tempCase-1];
                tResol[tempCase]=-1;
                tempCase--;
            }
            else{
                randomResolTab(tResol, nbBord, origine, (randomN + 1)%4, randomBegin);
            }
        }
        else if (randomN == 3){
            if(tResol[tempCase-nbBord]<tempVal && tResol[tempCase-nbBord]!=0 && tResol[tempCase-nbBord]!=-1){
                tempVal=tResol[tempCase-nbBord];
                tResol[tempCase]=-1;
                tempCase-=nbBord;
            }
            else{
                randomResolTab(tResol, nbBord, origine, (randomN + 1)%4, randomBegin);
            }
        }
        else if (randomN == 0){
            if(tResol[tempCase+nbBord]<tempVal && tResol[tempCase+nbBord]!=0 && tResol[tempCase+nbBord]!=-1){
                tempVal=tResol[tempCase+nbBord];
                tResol[tempCase]=-1;
                tempCase+=nbBord;
            }
            else{
                randomResolTab(tResol, nbBord, origine, (randomN + 1)%4, randomBegin);
            }
        }
    }
}

int resolTab(int *tResol, int nbBord, int origine, int fin){
    int tempVal = tResol[origine];
    int tempCase = origine;
    int randomBegin;
    do{ 
        randomBegin = rand()%4;

        for (int i = 0; i < 100; i++)
        {
            randomResolTab(tResol, nbBord, origine, -1, randomBegin);
        }
        
        for (int i = 0; i<nbBord*nbBord; i++){
            if(tResol[i]!=0 && tResol[i]!=-1)
                tResol[i]=1;
        }
        
        tResol[tempCase]=-1;
        if(tResol[tempCase+1]<tempVal && tResol[tempCase+1]!=0 && tResol[tempCase+1]!=-1){
            tempVal=tResol[tempCase+1];
            tResol[tempCase]=-1;
            tempCase++;
        }
        else if(tResol[tempCase-1]<tempVal && tResol[tempCase-1]!=0 && tResol[tempCase-1]!=-1){
            tempVal=tResol[tempCase-1];
            tResol[tempCase]=-1;
            tempCase--;
        }
        else if(tResol[tempCase-nbBord]<tempVal && tResol[tempCase-nbBord]!=0 && tResol[tempCase-nbBord]!=-1){
            tempVal=tResol[tempCase-nbBord];
            tResol[tempCase]=-1;
            tempCase-=nbBord;
        }
        else if(tResol[tempCase+nbBord]<tempVal && tResol[tempCase+nbBord]!=0 && tResol[tempCase+nbBord]!=-1){
            tempVal=tResol[tempCase+nbBord];
            tResol[tempCase]=-1;
            tempCase+=nbBord;
        }
        printTable(tResol, nbBord, 0);
    }while (tResol[fin]==1);
    for (int i = 0; i<nbBord*nbBord; i++){
        if(tResol[i]!=0 && tResol[i]!=-1)
            tResol[i]=1;
    }
}

int main(void)
{
    int *t = NULL, *tMove = NULL, *tResol = NULL, pointPos;
    int nbBord;
    int point;

    //-----------------------------------------------Initialisaytion du labyrinthe-----------------------------------------------------------//
    printf("\nHow much for the maze size ? ");
    scanf("%i", &nbBord);
    if (nbBord%2==0)
        nbBord++;

    t = calloc(nbBord*nbBord, sizeof(int)); ////Assignement de la m�moire de stockage du labyrinthe
    tMove = calloc(nbBord*nbBord, sizeof(int));
    tResol = calloc(nbBord*nbBord, sizeof(int));

    setupBlankTable(&t[0], nbBord);

    //-----------------------------------------------Cr�ation du labyrinthe int�rieur--------------------------------------------------------//
    creationLab(&t[0], nbBord);

    printTable(t, nbBord, 1);

    //-----------------------------------------------Partie r�solution du labyrinthe--------------------------------------------------------//
    for (int i=0; i<nbBord*nbBord; i++){
        tMove[i] = t[i];
    }

    tMove[nbBord*nbBord-nbBord]=2;
    calculateReverseTable(tMove, nbBord, nbBord*nbBord-1-nbBord);

    printTable(tMove, nbBord, 0);
    system("pause");

    //-----------------------------------------------Partie r�solution du labyrinthe le plus simplement-------------------------------------//
    for (int i=0; i<nbBord*nbBord; i++){
        tResol[i] = tMove[i];
    }


    system("cls");

    printf("\nLe labyrinthe est : \n\n");
    printTable(t, nbBord, 1);

    /*
    printf("\nVeux-tu placer un point a atteindre avant l'arrivee ? (1/0) ");
    scanf("%i", &point);*/
    if (point!=1){
        printf("\nSi vous continuez, vous obtiendrez la resolution du labyrinthe.");

        printf("\nLa resolution la plus simple du labyrinthe est : \n");
        resolTab(&tResol[0], nbBord, nbBord, nbBord*nbBord-1-nbBord);
    }/*
    else
    {
        for (int i=0; i<nbBord*nbBord; i++){
            tMove[i] = t[i];
        }
        do{
            printf("\nQuel point ? (entre 0 et %i ", nbBord*nbBord-1);
            scanf("%i", &pointPos);
            if(t[pointPos]!=1){
                printf("\nY'a un truc dessus...\n");
            }
        }while(t[pointPos]!=1);
        if (t[pointPos+1]==1)
            t[pointPos+1]=2;
        else if (t[pointPos-1]==1)
            t[pointPos-1]=2;
        else if (t[pointPos-nbBord]==1)
            t[pointPos-nbBord]=2;
        else if (t[pointPos+nbBord]==1)
            t[pointPos+nbBord]=2;
        int var=2;
        for (int i=0; i < nbBord*nbBord; i++){
            (&tMove[0], var, nbBord);
            var++;
        }
        resolTab(&tResol[0], nbBord, nbBord,pointPos);
    }*/

    free(tMove);
    free(t);
    free(tResol);
}
