 // Copyright By Zhaoxiaopeng


#include "Charater/AuraCharacterBase.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	
	PrimaryActorTick.bCanEverTick = false;
	
	//创建武器骨骼，设置骨骼插槽，将骨骼设置为无碰撞
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon"); 
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
}


void AAuraCharacterBase::BeginPlay() 
{
	Super::BeginPlay();
	
}


 
