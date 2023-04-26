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