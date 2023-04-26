#pragma once
//#include "entity.h"
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