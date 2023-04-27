#pragma once
#include <vector>
#include <string>
//#include "action.h"

class Action;

class Entity{
public:
    const std::string name;
    const int ATK;
    
    int GetHP();
    void SetHP(int n);
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
};

class Player : public Entity {
public:
    Player(std::string name = "Player", int hp = 15, int atk = 5);
    virtual ~Player() override {}
};

class Enemy : public Entity {
public:
    Enemy(std::string name, int hp, int atk);
    virtual ~Enemy() override {}
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