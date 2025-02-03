// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AK47.h"
#include "GameFramework/Character.h"

AAK47::AAK47()
{
	KindOfWeapon = EWeaponType::AK47;
	m_Ammo = 30;
	WeaponPrice = 1500;
}

void AAK47::EventTrigger_Implementation(bool IsPress)
{
	if (IsPress)
	{
		LoopShootMontage();
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.SetTimer(th_loopShoot, this, &AAK47::LoopShootMontage, 0.1f, true);
	}
	else
	{
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.ClearTimer(th_loopShoot);
	}
}

void AAK47::LoopShootMontage()
{
	if (IsValid(ShootMontage) == false)
		return;
	if (m_pOwnChar == nullptr || m_Ammo == 0)
		return;
	m_pOwnChar->PlayAnimMontage(ShootMontage);
}
