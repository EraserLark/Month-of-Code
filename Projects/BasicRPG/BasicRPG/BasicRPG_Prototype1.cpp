#include "main.h"

int main(int argc, char* argv[])
{
    bool isRunning = true;
    Texture* bgTextures = new Texture[4];
    Texture* enemySprites = new Texture[4];
    DrawMaterials drawMaterials;

    if (!Initialize(&drawMaterials))
    {
        return -1;
    }
    else if(!LoadMedia(bgTextures, enemySprites, &drawMaterials))
    {
        return -1;
    }
    else
    {
        Player player;
        StateStack stateStack;

        TextboxState* tbState = new TextboxState("Thanks for playing!", &stateStack, &drawMaterials);
        stateStack.PushState(tbState);

        DungeonState* dungeonState = new DungeonState(&stateStack, &player, bgTextures, enemySprites, &drawMaterials);
        stateStack.PushState(dungeonState);

        //Update
        while (isRunning)
        {
            SDL_Event event;
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            if (stateStack.TopState() != nullptr)
            {
                stateStack.TopState()->runCurrentState();
            }
            else
            {
                isRunning = false;
            }

            Draw(&drawMaterials);
        }
    }

    CleanUp(bgTextures, enemySprites, &drawMaterials);
    return 0;
}