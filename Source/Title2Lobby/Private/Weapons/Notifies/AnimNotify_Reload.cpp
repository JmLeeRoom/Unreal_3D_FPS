// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Notifies/AnimNotify_Reload.h"
#include "FP_FirstPerson/FPSCharacter.h"
#include "Weapons/WeaponInterface.h"

void UAnimNotify_Reload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AFPSCharacter* PlayCharacter = Cast<AFPSCharacter>(MeshComp->GetOwner());
	if (IsValid(PlayCharacter) == false)
		return;
	IWeaponInterface* WeaponInf = Cast<IWeaponInterface>(PlayCharacter->m_EquipWeapon);
	if (WeaponInf == nullptr)
		return;
	WeaponInf->Execute_EventResetAmmo(PlayCharacter->m_EquipWeapon);
}
