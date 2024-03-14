// Copyright By Zhaoxiaopeng

#pragma once

#include "CoreMinimal.h"
#include "Charater/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy ();



#pragma region EnemyInterface
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
#pragma endregion 

protected:
	virtual void BeginPlay() override;
};
