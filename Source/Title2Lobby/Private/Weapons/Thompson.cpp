// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Thompson.h"
#include "GameFramework/Character.h"

AThompson::AThompson()
{
	KindOfWeapon = EWeaponType::Thompson;
	m_Ammo = 30;
	WeaponPrice = 1000;
	
}

void AThompson::EventTrigger_Implementation(bool IsPress)
{
	if (IsPress)
	{
		LoopShootMontage();
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.SetTimer(th_loopShoot, this, &AThompson::LoopShootMontage, 0.09f, true);
	}
	else
	{
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.ClearTimer(th_loopShoot);
	}
}

void AThompson::LoopShootMontage()
{
	if (IsValid(ShootMontage) == false)
		return;
	if (m_pOwnChar == nullptr || m_Ammo == 0)
		return;
	m_pOwnChar->PlayAnimMontage(ShootMontage);
}
