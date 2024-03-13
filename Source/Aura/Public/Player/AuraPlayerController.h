// Copyright By Zhaoxiaopeng

#pragma once

//#include "InputMappingContext.h"   使用前向声明，不必包含头文件
#include "CoreMinimal.h"
//#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class UInputMappingContext;  //前向声明
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AAuraPlayerController();

protected:

	virtual  void BeginPlay() override;
	virtual  void SetupInputComponent() override;

private:
	
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;


	void Move(const  FInputActionValue& InputActionValue);
};
