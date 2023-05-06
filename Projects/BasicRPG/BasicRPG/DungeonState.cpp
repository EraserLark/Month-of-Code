#include "DungeonState.h"
#include "BattleState.h"

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

	this->bgTextures = bgTextures;
	this->enemySprites = enemySprites;

	Enemy* Shrub = new Enemy("Shrub Gremlin", 5, 3, &enemySprites[0]);
	Shrub->SetAction(new PhysicalAttack("Shrub-o mode", 1, Shrub, player));
	Level* level1 = new Level(Shrub, &bgTextures[0], "A shrub blocks the path.");
	dungeonQueue.Enqueue(level1);

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
}

Texture* DungeonState::GetEnemySprite()
{
	if (dungeonQueue.GetHead() != nullptr)
	{
		Texture* enemySpr = dungeonQueue.GetHead()->enemy->GetSprite();
		return enemySpr;
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