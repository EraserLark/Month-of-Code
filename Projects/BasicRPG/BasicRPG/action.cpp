#include "action.h"
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