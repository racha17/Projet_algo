#include <stdio.h>
#include <stdlib.h>

typedef struct fileReq
{
    int nbr;
    struct fileReq *svt;
} fileReq;
typedef struct fileReq
{
    int nbr;
    struct fileReq *svt;
} fileReq;

void enfiler(fileReq *fileReq, int val)
{
    int x;
    struct fileReq *L, *P;
    P = malloc(sizeof(fileReq));

    P->nbr = x;
    P->svt = NULL;
    if (P->svt != NULL)
    {
        L = P;
        while (L->svt != NULL)
        {
            L = L->svt;
        }
        L->svt = P;
    }
    else
    {
        fileReq = P;
    }
}
int defiler(fileReq *file, int *val)
{
    int nbrDeFile = 0;
    if (file != NULL)
    {
    }
}

int main()
{
}
