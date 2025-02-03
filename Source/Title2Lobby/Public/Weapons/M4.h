// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "M4.generated.h"

/**
 * 
 */
UCLASS()
class TITLE2LOBBY_API AM4 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AM4();

	virtual void EventTrigger_Implementation(bool IsPress) override;

	void LoopShootMontage();

	FTimerHandle th_loopShoot;
};
