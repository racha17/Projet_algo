#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
typedef struct list
{
    int nbr;
    struct list *svt;
} list;
typedef struct Pile
{
    list *first;
} Pile;

#endif // STRUCTURES_H_INCLUDED



