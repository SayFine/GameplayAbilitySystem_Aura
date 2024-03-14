// Copyright By Zhaoxiaopeng

 
#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	
	bReplicates = true;
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();

	
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	/*
	 * 光标射线追踪：有以下几种情况:
	 * A. lastActor is null && ThisActor is null
	 *		-如果是以上情况,那么我们什么都不做
	 * B. lastActor is null && ThisActor is valid
	 *		-如果是以上情况，那么我们应该给ThisActor 加上高光效果
	 * C. lastActor is valid && ThisActor is null
	 *		-如果是以上情况，那么我们应该给LastActor 取消高光效果
	 * D. 如果lastActor 和 ThisActor 都存在, 但是lastActor != ThisActor
	 *		-如果是以上情况，那么我们把LastActor的高光效果取消,给ThisActor增加高光效果
	 * E. 如果lastActor 和 ThisActor 都存在, 而且lastActor = ThisActor
	 *		-如果是以上情况,那么我们什么都不做
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr )
		{
			//B.给ThisActor 加上高光效果
			ThisActor->HighLightActor();
		}
		else
		{
			//A. 什么都不做
		}
	}
	else
	{
		if(ThisActor ==nullptr )
		{
			//C.给LastActor 取消高光效果
			LastActor->UnHighLightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				//D.把LastActor的高光效果取消,给ThisActor增加高光效果
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
			else
			{
				//E.什么都不做
			}

		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//如果输入无效，停止游戏
	check(AuraContext);

	//添加增强本地玩家输入子系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	check(Subsystem);

	//设置移动输入优先级
	Subsystem->AddMappingContext(AuraContext,0);

	//设置鼠标输入模式 
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation (0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllePawn   = GetPawn<APawn>())
	{
		ControllePawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControllePawn->AddMovementInput(RightDirection,InputAxisVector.X);
		
	}
	
}


