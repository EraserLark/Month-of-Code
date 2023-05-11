#include "entity.h"
#include "action.h"

int Entity::GetHP() { return HP; }
void Entity::SetHP(int n) { HP = n; }

int Entity::GetDEF() { return DEF; }
void Entity::SetDEF(int n) { DEF = n; }
void Entity::ResetDEF() { DEF = 0; }

Action* Entity::GetAction(int n) { return actions[n]; }
void Entity::SetAction(Action* actionPtr) { actions.push_back(actionPtr); }

void Entity::SetOpponent(Entity* target)
{
    for (Action* action : actions)
    {
        action->SetTarget(target);
    }
}

void Entity::TakeDamage(const int dmg)
{
    int trueDmg = dmg - this->DEF;
    if (trueDmg < 0) trueDmg = 0;
    HP -= trueDmg;
    if (HP < 0) HP = 0;
}

Entity::~Entity()
{
    for (Action* action : actions)
    {
        delete action;
    }
    actions.clear();
};

Entity::Entity(std::string entName, int hp, int atk)
    :ATK{ atk }, name{ entName }{
    SetHP(hp);
    DEF = 0;
}

Player::Player(std::string name, int hp, int atk)
    : Entity(name, hp, atk) {
    SetAction(new PhysicalAttack("Attack", 3, this, nullptr));
    SetAction(new PhysicalAttack("Spec Attack", 4, this, nullptr));
    SetAction(new Defend("Defend", 2, this, nullptr));
}

Enemy::Enemy(std::string name, int hp, int atk, Texture* sprite)
    : Entity(name, hp, atk) {
    this->sprite = sprite;
};