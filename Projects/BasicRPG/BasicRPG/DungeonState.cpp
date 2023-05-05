#include "DungeonState.h"
#include "BattleState.h"

Level::Level(Enemy* enemy, Texture* bgTexture, std::string openingLine)
{
	this->enemy = enemy;
	this->bgTexture = bgTexture;
	this->openingLine = openingLine;
}

DungeonState::DungeonState(StateStack* stateStack, Player* player, Texture* bgTextures, Texture* enemySprites)
	:State(stateStack)
{
	this->stateStack = stateStack;
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
			battleState = new BattleState(stateStack, player, &dungeonQueue);
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
	Texture* bgTexture = dungeonQueue.GetHead()->bgTexture;
	return bgTexture;
}

Texture* DungeonState::GetEnemySprite()
{
	Texture* enemySpr = dungeonQueue.GetHead()->enemy->GetSprite();
	return enemySpr;
}

bool DungeonState::CheckDungeonQueueEmpty()
{
	return dungeonQueue.IsEmpty();
}