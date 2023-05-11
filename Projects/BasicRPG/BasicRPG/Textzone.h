#pragma once
#include "Texture.h"

class TextZone {
public:
    void SetRenderer(SDL_Renderer* mainRenderer) { tzRenderer = mainRenderer; }
    void SetFont(TTF_Font* font) { tzFont = font; }

    void Show() { hideTextzone = false; }
    void Hide() { hideTextzone = true; }

    void RenderTZ();
    virtual void Render() = 0;
    virtual void Destroy() = 0;

    virtual ~TextZone();
protected:
    TextZone(DrawMaterials*);

    SDL_Renderer* tzRenderer;
    TTF_Font* tzFont;
    DrawMaterials* drawMaterials;
    SDL_Rect tzRect;
    SDL_Color fontColor;
    bool hideTextzone;
};


class Textbox : public TextZone {
public:
    Textbox(DrawMaterials*);

    void NewText(std::string message);

    virtual void Render() override;
    virtual void Destroy() override;

    ~Textbox();
private:
    Texture textTexture;
};


class Menu : public TextZone {
public:
    Menu(DrawMaterials*, std::string*);

    void IncrementSelection();
    void DecrementSelection();
    int ConfirmSelection();
    void MoveCursor();

    virtual void Render() override;
    virtual void Destroy() override;

    ~Menu();
private:
    const int choiceCount = 3;
    Texture choiceTextures[3];
    int playerChoice;
    SDL_Rect cursor;
};