#include <iostream>
#include "action.h"
#include "entity.h"

//Base Class
Action::Action(std::string n, Entity* sen, Entity* tar)
    : name{ n }
{
    sender = sen;
    target = tar;
}

Entity* Action::GetSender() { return sender; }
Entity* Action::GetTarget() { return target; }
void Action::SetTarget(Entity* targ) { target = targ; }

Action::~Action() { }

//Physical Attack
PhysicalAttack::PhysicalAttack(std::string str, int baseDmg, Entity* e1, Entity* e2)
    : Action(str, e1, e2), baseDamage{ baseDmg } { }

void PhysicalAttack::runAction()
{
    //int damage = sender->ATK + RandomNum();
    int damage = baseDamage;
    if (damage <= 0)
    {
        std::cout << "MISS!!" << std::endl;
    }
    else
    {
        target->TakeDamage(damage);
    }
}