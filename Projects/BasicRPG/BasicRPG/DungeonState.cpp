#include "DungeonState.h"
#include "action.h"
#include "entity.h"
#include "queue.h"
#include "Texture.h"
#include "BattleState.h"
#include "SDLfoundation.h"
#include "StateMachine.h"

Level::Level(Enemy* enemy, Texture* bgTexture, std::string openingLine)
{
	this->enemy = enemy;
	this->bgTexture = bgTexture;
	this->openingLine = openingLine;
}

DungeonState::DungeonState(StateStack* stateStack, Player* player, Texture* bgTextures, Texture* enemySprites, DrawMaterials* drawMaterials)
	:State(stateStack)
{
	this->stateStack = stateStack;
	this->drawMaterials = drawMaterials;
	this->player = player;
	battleState = nullptr;

	this->bgTextures = bgTextures;
	this->enemySprites = enemySprites;

	Enemy* Shrub = new Enemy("Shrub Gremlin", 5, 3, &enemySprites[0]);
	Shrub->SetAction(new PhysicalAttack("Shrub-o mode", 1, Shrub, player));
	Level* level1 = new Level(Shrub, &bgTextures[0], "A shrub blocks the path.");
	dungeonQueue.Enqueue(level1);

	Enemy* Snow = new Enemy("Snow Grump", 8, 5, &enemySprites[1]);
	Snow->SetAction(new PhysicalAttack("Spearsicle", 2, Snow, player));
	Level* level2 = new Level(Snow, &bgTextures[1], "A snowman blocks the path.");
	dungeonQueue.Enqueue(level2);

	Enemy* Flame = new Enemy("Flame Bro", 10, 7, &enemySprites[2]);
	Flame->SetAction(new PhysicalAttack("Burning Abs", 3, Flame, player));
	Level* level3 = new Level(Flame, &bgTextures[2], "A flameman blocks the path.");
	dungeonQueue.Enqueue(level3);

	Enemy* Light = new Enemy("???", 12, 9, &enemySprites[3]);
	Light->SetAction(new PhysicalAttack("Lightning Blast", 4, Light, player));
	Level* level4 = new Level(Light, &bgTextures[3], "Something strong blocks the path.");
	dungeonQueue.Enqueue(level4);

	currentState = subState::NewLevel;
}

void DungeonState::runCurrentState()
{
	Level* currentLevel;

	switch (currentState)
	{
	case subState::NewLevel:
		currentLevel = dungeonQueue.GetHead();
		if (currentLevel == nullptr)
		{
			currentState = subState::Finish;
		}
		else
		{
			drawMaterials->bgTexture = currentLevel->bgTexture;
			drawMaterials->enemySprite = currentLevel->enemy->GetSprite();

			battleState = new BattleState(stateStack, player, &dungeonQueue, drawMaterials);
			stateStack->PushState(battleState);
			currentState = subState::Active;
		}
		break;
	case subState::Active:
		currentState = subState::NewLevel;
		break;
	case subState::Finish:
		Exit();
		break;
	}
}

void DungeonState::Exit()
{
	stateStack->StateFinish();
}

Texture* DungeonState::GetBGTexture()
{
	if (dungeonQueue.GetHead() != nullptr)
	{
		Texture* bgTexture = dungeonQueue.GetHead()->bgTexture;
		return bgTexture;
	}
	else
	{
		return nullptr;
	}
}

Texture* DungeonState::GetEnemySprite()
{
	if (dungeonQueue.GetHead() != nullptr)
	{
		Texture* enemySpr = dungeonQueue.GetHead()->enemy->GetSprite();
		return enemySpr;
	}
	else
	{
		return nullptr;
	}
}

bool DungeonState::CheckDungeonQueueEmpty()
{
	return dungeonQueue.IsEmpty();
}

DungeonState::~DungeonState()
{
	dungeonQueue.EmptyQueue();
	bgTextures = nullptr;
	enemySprites = nullptr;
	player = nullptr;
	stateStack = nullptr;
	battleState = nullptr;
}