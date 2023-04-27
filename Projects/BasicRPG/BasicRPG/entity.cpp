#include "entity.h"
#include "action.h"

int Entity::GetHP() { return HP; }
void Entity::SetHP(int n) { HP = n; }

Action* Entity::GetAction(int n) { return actions[n]; }
void Entity::SetAction(Action* actionPtr) { actions.push_back(actionPtr); }

void Entity::SetOpponent(Entity* target)
{
    for (Action* action : actions)
    {
        action->SetTarget(target);
    }
}

void Entity::TakeDamage(int dmg) { HP -= dmg; if (HP < 0)  HP = 0; }

Entity::~Entity()
{
    for (Action* action : actions)
    {
        delete action;
    }
    actions.clear();
};

Entity::Entity(std::string entName, int hp, int atk)
    :ATK{ atk }, name{ entName }
    {SetHP(hp); }