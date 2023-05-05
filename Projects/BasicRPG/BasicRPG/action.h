#pragma once
#include "entity.h"
#include <string>

class Entity;

class Action{
public:
    const std::string name;

    Entity* GetSender();
    Entity* GetTarget();
    void SetTarget(Entity* targ);
    
    virtual ~Action();
    virtual void runAction() = 0;     //Pure virtual function

protected:
    Action(std::string, Entity*, Entity*);
    Entity* sender;
    Entity* target;
};

class PhysicalAttack : public Action {
public:
    PhysicalAttack(std::string str, int baseDmg, Entity* e1, Entity* e2);
    virtual void runAction() override;
private:
    const int baseDamage;
};