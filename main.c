/*          Chemin de code pour atteindre ce programme. Attention, il faut se placer à l'intérieur du dossier contenant bin, lib, include et src

gcc main.c -o bin/prog
bin/prog

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define test printf("------------------------test------------------------")

void afficheTableauI(int *t, int nbBord)
{
    for(int i = 0; i<nbBord;i++){
        for(int j = 0; j<nbBord; j++){
            printf("[%i] ", t[i*nbBord+j]);
        }
        printf("De %i a %i", i*nbBord, i*nbBord+nbBord);
        printf("\n");
    }
}

void afficheTableauC(char *t, int nbBord)
{
    for(int i = 0; i<nbBord;i++){
        for(int j = 0; j<nbBord; j++){
            printf("%c", t[i*nbBord+j]);
        }
        printf("De %i a %i", i*nbBord, i*nbBord+nbBord);
        printf("\n");
    }
}


void setup(int *t, int nbBord) /////V�rification : OK
{
    //-----------------------------------------------Mise en place des cases pr�d�finies du tableau-----------------------------------------//
    for (int i = 0; i<nbBord; i++){
            for(int j = 0; j<nbBord; j++){
                t[i*nbBord+j]=(i*nbBord+j)+100;
                if (i%2==0 || j%2==0)
                    t[i*nbBord+j]=0;
            }
    }
    t[nbBord+1]=1; //Initialise la premi�re case du labyrinthe � 1
    srand(time(NULL));
}

int verifTab(int *t, int nbBord) /////V�rification : OK
{
    for(int i=0; i<nbBord*nbBord; i++){
        if(t[i]!=0 && t[i]!=1){
            return 0;
        }
    }
    return 1;
}

int convertTab (int *t, int nbBord, int type)
{
    char *tab;
    tab = calloc(nbBord*nbBord, sizeof(char));
    if(type == 0){
        for (int i = 0; i<nbBord; i++){
            for (int j = 0; j<nbBord; j++){
                if (t[i*nbBord+j]==0){
                    tab[i*nbBord+j] = 178;
                }
                else if (t[i*nbBord+j]==1){
                    tab[i*nbBord+j] = 177;
                }
                else {
                    printf("\nY'a un probleme en case numero : %i\n",i*nbBord+j+1);
                    system("pause");
                }
            }
        }
    }
    if(type == 1){
        for (int i = 0; i<nbBord; i++){
            for (int j = 0; j<nbBord; j++){
                if (t[i*nbBord+j]==0){
                    tab[i*nbBord+j] = 178;
                }
                else if (t[i*nbBord+j]==1){
                    tab[i*nbBord+j] = 177;
                }
                else if (t[i*nbBord+j]==-1){
                    tab[i*nbBord+j] = ' ';
                }
                else {
                    printf("\nY'a un probleme en case numero : %i\n", i*nbBord+j+1);
                    system("pause");
                }
            }
        }
    }
    afficheTableauC(&tab[0], nbBord);
    free(tab);
}


int creationLab(int *t, int nbBord) /////V�rification : OK
{
    int randomValue, randomValueB, temp;
    //-----------------------------------------------Cr�ation du labyrinthe------------------------------------------------------------------//
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
    }while(verifTab(&t[0], nbBord)==0);
    //-----------------------------------------------Cr�ation des sorties du labyrinthe------------------------------------------------------//
    t[nbBord]=1;
    t[nbBord*nbBord-1-nbBord]=1;
}

int nextMove(int *tMove, int origine, int nbBord)
{
    for (int i=0; i<nbBord*nbBord; i++){
        if(tMove[i]==origine && i != nbBord*nbBord-1-nbBord){
            for(int j=0; j<4; j++){
                if (tMove[i+1]!=0 && tMove[i+1]==1 && (i+1)!= nbBord*nbBord-1-nbBord){
                    tMove[i+1]=origine+1;
                }
                else if (tMove[i-1]!=0 && tMove[i-1]==1 && (i-1)!= nbBord*nbBord-1-nbBord){
                    tMove[i-1]=origine+1;
                }
                else if (tMove[i-nbBord]!=0 && tMove[i-nbBord]==1 && (i-nbBord)!= nbBord*nbBord-1-nbBord){
                    tMove[i-nbBord]=origine+1;
                }
                else if (tMove[i+nbBord]!=0 && tMove[i+nbBord]==1 && (i+nbBord)!= nbBord*nbBord-1-nbBord){
                    tMove[i+nbBord]=origine+1;
                }
            }
        }
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
        //convertTab(&tResol[0], nbBord, 1);
        
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
        afficheTableauI(tResol, nbBord);
    }while (tResol[fin]==1);
    for (int i = 0; i<nbBord*nbBord; i++){
        if(tResol[i]!=0 && tResol[i]!=-1)
            tResol[i]=1;
    }
    convertTab(&tResol[0], nbBord, 1);

}

int main(void)
{
    int *t = NULL, *tMove = NULL, *tResol = NULL, pointPos;
    int nbBord;
    int point;

    //-----------------------------------------------Initialisaytion du labyrinthe-----------------------------------------------------------//
    printf("\nCombien de lignes/colonnes ? ");
    scanf("%i", &nbBord);
    if (nbBord%2==0)
        nbBord++;

    t = calloc(nbBord*nbBord, sizeof(int)); ////Assignement de la m�moire de stockage du labyrinthe
    tMove = calloc(nbBord*nbBord, sizeof(int));
    tResol = calloc(nbBord*nbBord, sizeof(int));

    setup(&t[0], nbBord);

    //-----------------------------------------------Cr�ation du labyrinthe int�rieur--------------------------------------------------------//
    creationLab(&t[0], nbBord);

    convertTab(&t[0], nbBord, 0);

    //-----------------------------------------------Partie r�solution du labyrinthe--------------------------------------------------------//
    for (int i=0; i<nbBord*nbBord; i++){
        tMove[i] = t[i];
    }
    tMove[nbBord*nbBord-1-nbBord]=1;
    if(tMove[nbBord*nbBord-2-nbBord]!=0)
        tMove[nbBord*nbBord-2-nbBord]=2;
    int var=2;
    for (int i=0; i < nbBord*nbBord; i++){
        nextMove(&tMove[0], var, nbBord);
        var++;
    }

    //-----------------------------------------------Partie r�solution du labyrinthe le plus simplement-------------------------------------//
    for (int i=0; i<nbBord*nbBord; i++){
        tResol[i] = tMove[i];
    }


    system("cls");

    printf("\nLe labyrinthe est : \n\n");
    convertTab(&t[0],nbBord,0);


    printf("\nVeux-tu placer un point a atteindre avant l'arrivee ? (1/0) ");
    scanf("%i", &point);
    if (point!=1){
        printf("\nSi vous continuez, vous obtiendrez la resolution du labyrinthe.");

        printf("\nLa resolution la plus simple du labyrinthe est : \n");
        resolTab(&tResol[0], nbBord, nbBord, nbBord*nbBord-1-nbBord);
    }
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
            nextMove(&tMove[0], var, nbBord);
            var++;
        }
        resolTab(&tResol[0], nbBord, nbBord,pointPos);
    }

    free(tMove);
    free(t);
    free(tResol);
}
