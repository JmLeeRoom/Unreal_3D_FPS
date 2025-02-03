// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "Thompson.generated.h"

/**
 * 
 */
UCLASS()
class TITLE2LOBBY_API AThompson : public AWeaponBase
{
	GENERATED_BODY()
public:
	AThompson();

	virtual void EventTrigger_Implementation(bool IsPress) override;

	void LoopShootMontage();

	FTimerHandle th_loopShoot;
};
