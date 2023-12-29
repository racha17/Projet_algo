#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "structure.h"
#include "F_predefinies.h"
#include "Fonctions.h"

void drawRectanglePile(Pile *pile, int posX, int posY, int spacing, Color color)
{
    int count = 0;
    list *current = pile->first;
    while (current != NULL)
    {
        DrawRectangle(posX, posY - count * spacing, 50, 30, color);
        current = current->svt;
        count++;
    }
}
int main()
{

    // Pile Mapile = initPile();
    // int N, val;

    // printf("entrez le max de valeurs que peut contenir la pile:\n");
    // scanf("%d", &N);

    // for (int i = 0; i < N; i++)
    // {
    //     scanf("%d", &val);
    //     empiler(&Mapile, val);
    // }
    // printf("les valeurs de la pile sont:\n");
    // afficher(&Mapile);

    // printf("donnez la valeur que vous voulez supprimer:\n");
    // scanf("%d", &val);

    // suppression(&Mapile, val);
    // afficher(&Mapile);

    // printf("veuillez donner la valeur que vous voulez rechercher:\n");
    // scanf("%d", &val);
    // if (recherche(&Mapile, val) == false)
    // {
    //     printf("la valeur existe n'existe pas\n ");
    // }
    // else
    // {
    //     printf("la valeur existe . \n");
    // }
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Pile Implementation with Raylib");

    // Create pile and fill with data
    Pile Mapile = initPile();
    int N, val;

    printf("Enter the max number of values that can be contained in the pile:\n");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &val);
        empiler(&Mapile, val);
    }

    // Main game loop
    while (!WindowShouldClose())
    {

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        drawRectanglePile(&Mapile, 200, 200, 40, BLUE);

        DrawText("Press ESC to close", 10, 10, 20, GRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context
}
