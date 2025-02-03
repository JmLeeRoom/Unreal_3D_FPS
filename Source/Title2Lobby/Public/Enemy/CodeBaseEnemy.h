// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CodeBaseEnemy.generated.h"

UCLASS()
class TITLE2LOBBY_API ACodeBaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACodeBaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateHP(float Damage, APlayerController* CurPlayer);

	void UpdateHP_Implementation(float Damage, APlayerController* CurPlayer);
};
