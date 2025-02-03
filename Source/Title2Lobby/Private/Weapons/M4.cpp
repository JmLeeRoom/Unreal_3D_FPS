// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/M4.h"
#include "GameFramework/Character.h"

AM4::AM4()
{
	KindOfWeapon = EWeaponType::M4A1;
	m_Ammo = 30;
	WeaponPrice = 3000;
}

void AM4::EventTrigger_Implementation(bool IsPress)
{
	if (IsPress)
	{
		LoopShootMontage();
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.SetTimer(th_loopShoot, this, &AM4::LoopShootMontage, 0.08f, true);
	}
	else
	{
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.ClearTimer(th_loopShoot);
	}
}

void AM4::LoopShootMontage()
{
		if (IsValid(ShootMontage) == false)
		return;
	if (m_pOwnChar == nullptr || m_Ammo == 0)
		return;
	m_pOwnChar->PlayAnimMontage(ShootMontage);
}
