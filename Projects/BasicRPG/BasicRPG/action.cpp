#include "action.h"
#include <iostream>
#include "entity.h"

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


PhysicalAttack::PhysicalAttack(std::string name, int baseDmg, Entity* e1, Entity* e2)
    : Action(name, e1, e2), baseDamage{ baseDmg } { }

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


Defend::Defend(std::string name, int defAmt, Entity* e1, Entity* e2)
    :Action(name, e1, e2), defenseAmt{ defAmt } {}

void Defend::runAction()
{
    sender->SetDEF(2);
}