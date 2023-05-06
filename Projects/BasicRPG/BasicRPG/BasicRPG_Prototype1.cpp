#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
    Texture* bgTextures = new Texture[4];
    Texture* enemySprites = new Texture[4];
    DrawMaterials drawMaterials;
    drawMaterials.currentMenu = nullptr;
    drawMaterials.currentTB = nullptr;

    if (Initialize() != 0)
    {
        return -1;
    }
    else if(!LoadMedia(bgTextures, enemySprites))
    {
        return -1;
    }
    else
    {
        Player* p = new Player();
        Enemy* e = nullptr;

        StateStack stateStack;

        TextboxState* tbState = new TextboxState("Thanks for playing!", &stateStack, &drawMaterials);
        stateStack.PushState(tbState);

        DungeonState* dungeonState = new DungeonState(&stateStack, p, bgTextures, enemySprites, &drawMaterials);
        stateStack.PushState(dungeonState);

        //Update
        while (isRunning)
        {
            //Event Handling
            SDL_Event event;

            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            //State Stack
            if (stateStack.TopState() != nullptr)
            {
                stateStack.TopState()->runCurrentState();
            }
            else
            {
                isRunning = false;
            }

            //Drawing
            Draw(&drawMaterials);
        }
    }

    CleanUp(&drawMaterials);

    return 0;
}