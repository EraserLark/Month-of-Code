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

Player::Player(std::string name, int hp, int atk)
    : Entity(name, hp, atk) {
    SetAction(new PhysicalAttack("Regular Attack", 3, this, nullptr));
    SetAction(new PhysicalAttack("Special Attack", 4, this, nullptr));
    SetAction(new PhysicalAttack("Witty Attack?", 5, this, nullptr));
    SetAction(new PhysicalAttack("Bounce Attack", 6, this, nullptr));
}

Enemy::Enemy(std::string name, int hp, int atk)
    : Entity(name, hp, atk) { };

Goblin::Goblin()
    : Enemy("Goblin", 7, 3) {
    SetAction(new PhysicalAttack("Goblin Attack", 5, this, nullptr));
    SetAction(new PhysicalAttack("Special Goblin Attack", 5, this, nullptr));
    SetAction(new PhysicalAttack("Goblin Gutpunch", 5, this, nullptr));
    SetAction(new PhysicalAttack("Piroutte", 5, this, nullptr));
};