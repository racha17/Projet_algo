#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

struct list
{
    int nbr;
    struct list *svt;
};

struct list *creerListe(int N);
void afficher(struct list *tete);
void libererListe(struct list *tete);
struct list *InsererElement(struct list *tete, int N, int val, int pos);
struct list *SuppElement(struct list *tete, int val);
int Recherche(struct list *tete, int val);
struct list *TrieParSelection(struct list *tete);
struct list *TrieParInsertion(struct list *tete);

#endif // LISTE_H_INCLUDED
