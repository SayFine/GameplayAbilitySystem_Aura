 // Copyright By Zhaoxiaopeng


#include "Charater/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

 AAuraCharacter::AAuraCharacter()
 {
 
  GetCharacterMovement()->bOrientRotationToMovement = true;
  GetCharacterMovement()->RotationRate  = FRotator(0.f,400.f,0.f);
  GetCharacterMovement()->bConstrainToPlane = true;
  GetCharacterMovement()->bSnapToPlaneAtStart = true;
  
  bUseControllerRotationPitch = false;
  bUseControllerRotationRoll = false;
  bUseControllerRotationYaw = false;
  
 }

 void AAuraCharacter::PossessedBy(AController* NewController)
 {
     Super::PossessedBy(NewController);

 	//在服务器 初始化 Ability actor info
 	InitAbilityActorInfo();
 } 

 void AAuraCharacter::OnRep_PlayerState()
 {
     Super::OnRep_PlayerState();
 	//在客户端 初始化 Ability actor info
 	InitAbilityActorInfo();
  
 }

 void AAuraCharacter::InitAbilityActorInfo()
 { 

 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
 	check(AuraPlayerState);
 	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
 	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
 	AttributeSet = AuraPlayerState->GetAttributeSet();
 }
