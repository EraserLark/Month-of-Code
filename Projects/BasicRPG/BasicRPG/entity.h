#pragma once
#include "action.h"
#include <vector>
#include <string>

class Action;
class Texture;

class Entity{
public:
    const std::string name;
    const int ATK;
    
    int GetHP();
    void SetHP(int n);
    int GetDEF();
    void SetDEF(int n);
    void ResetDEF();
    Action* GetAction(int n);
    void SetAction(Action* actionPtr);
    void SetOpponent(Entity* target);

    virtual void TakeDamage(int dmg);
    virtual ~Entity();
protected:
    Entity(std::string entName, int hp, int atk);
private:
    std::vector<Action*> actions;
    int HP;
    int DEF;
};

class Player : public Entity {
public:
    Player(std::string name = "Player", int hp = 20, int atk = 5);
    virtual ~Player() override {}
};

class Enemy : public Entity {
public:
    Enemy(std::string name, int hp, int atk, Texture* sprite);
    virtual ~Enemy() override {}
    Texture* GetSprite() { return sprite; }
private:
    Texture* sprite;
};

class Goblin : public Enemy {
public:
    Goblin();
    virtual ~Goblin() override {}
};

class Wizard : public Enemy {
public:
    Wizard();
    virtual ~Wizard() override {}
};