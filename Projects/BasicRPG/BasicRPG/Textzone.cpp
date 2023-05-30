#include "Textzone.h"
#include "Texture.h"
#include <SDL.h>
#include "SDLfoundation.h"

TextZone::TextZone(DrawMaterials* drawMat)
{
    drawMaterials = drawMat;
    tzRect = { 25, drawMat->ScreenHeight - 100, drawMat->ScreenWidth - 50, 75 };
    fontColor = { 0,0,0,0 };
    hideTextzone = true;

    SetRenderer(drawMaterials->renderer);
    SetFont(drawMaterials->font);
}

void TextZone::RenderTZ()
{
    if (!hideTextzone)
    {
        SDL_SetRenderDrawColor(tzRenderer, 255, 255, 255, 0);
        SDL_RenderFillRect(tzRenderer, &tzRect);
        SDL_SetRenderDrawColor(tzRenderer, 0, 0, 0, 0);
    }
}

TextZone::~TextZone()
{
    tzRenderer = nullptr;
    tzFont = nullptr;
}


Textbox::Textbox(DrawMaterials* drawMat)
    :TextZone(drawMat)
{
    textTexture.SetPosition(drawMat->textRect.x, drawMat->textRect.y);
}

void Textbox::NewText(std::string message)
{
    textTexture.LoadText(tzFont, message, fontColor, tzRenderer);
}

void Textbox::Render()
{
    if (!hideTextzone)
    {
        RenderTZ();
        textTexture.RenderText(tzRenderer);
    }
}

void Textbox::Destroy()
{
    textTexture.DestroyTexture();
}

Textbox::~Textbox()
{
    Destroy();
}


Menu::Menu(DrawMaterials* drawMat, std::string* optionText)
    :TextZone(drawMat)
{
    playerChoice = 0;
    cursor = { 0,0,0,0 };

    int tzWidth = tzRect.w / 3;
    int tzHeight = tzRect.h;

    cursor.y = tzRect.y + 5;
    cursor.w = tzWidth;
    cursor.h = tzHeight - 10;
    MoveCursor();

    for (int i = 0; i < choiceCount; i++)
    {
        choiceTextures[i].LoadText(tzFont, optionText[i], fontColor, tzRenderer);

        int textWidth = choiceTextures[i].GetWidth();
        int textHeight = choiceTextures[i].GetHeight();

        int newx = tzRect.x + (tzWidth * i) + ((tzWidth / 2) - (textWidth / 2));
        int newy = tzRect.y + (tzHeight / 2) - (textHeight / 2);

        choiceTextures[i].SetPosition(newx, newy);
    }
}

void Menu::IncrementSelection()
{
    playerChoice++;
    if (playerChoice > 2)
    {
        playerChoice = 0;
    }

    MoveCursor();
}

void Menu::DecrementSelection()
{
    playerChoice--;
    if (playerChoice < 0)
    {
        playerChoice = 2;
    }

    MoveCursor();
}

int Menu::ConfirmSelection()
{
    return playerChoice;
}

void Menu::MoveCursor()
{
    int moveAmt = playerChoice;
    cursor.x = tzRect.x + (cursor.w * moveAmt);
}

void Menu::Render()
{
    if (!hideTextzone)
    {
        RenderTZ();

        for (int i = 0; i < choiceCount; i++)
        {
            choiceTextures[i].RenderText(tzRenderer);
        }

        SDL_SetRenderDrawColor(tzRenderer, 255, 0, 0, 0);
        SDL_RenderDrawRect(tzRenderer, &cursor);
        SDL_SetRenderDrawColor(tzRenderer, 0, 0, 0, 0);
    }
}

void Menu::Destroy()
{
    for (int i = 0; i < choiceCount; i++)
    {
        choiceTextures[i].DestroyTexture();
    }
}

Menu::~Menu()
{
    Destroy();
}