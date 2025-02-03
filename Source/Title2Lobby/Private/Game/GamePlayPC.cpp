// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GamePlayPC.h"
#include "Weapons/WeaponBase.h"
#include "Weapons/Beretta.h"
#include "Weapons/Thompson.h"
#include "Weapons/AK47.h"
#include "Weapons/M4.h"
#include "Items/ItemBase.h"
#include "FP_FirstPerson/FPSCharacter.h"
#include "FP_FirstPerson/FPSPlayerState.h"
#include "Kismet/GameplayStatics.h"

void AGamePlayPC::ServerBuyPistol_Implementation()
{
	AFPSCharacter* pCharacter = Cast<AFPSCharacter>(GetPawn());
	if (pCharacter)
	{
		// 스폰시키기
		// 스폰위치
		FVector SpawnedLocation = pCharacter->GetActorLocation() + pCharacter->GetActorForwardVector() * 100;

		// pCharacter의 회전 값을 가져옵니다.
		FRotator SpawnedRotation = pCharacter->GetActorRotation();

		ABeretta* PCPistol = GetWorld()->SpawnActor<ABeretta>(PistolClass, SpawnedLocation, SpawnedRotation);

	}
}

void AGamePlayPC::ServerBuyThompson_Implementation()
{
	AFPSCharacter* pCharacter = Cast<AFPSCharacter>(GetPawn());
	if (pCharacter)
	{
		// 스폰시키기
		// 스폰위치
		FVector SpawnedLocation = pCharacter->GetActorLocation() + pCharacter->GetActorForwardVector() * 100;

		// pCharacter의 회전 값을 가져옵니다.
		FRotator SpawnedRotation = pCharacter->GetActorRotation();

		AThompson* PCThompson = GetWorld()->SpawnActor<AThompson>(ThompsonClass, SpawnedLocation, SpawnedRotation);

	}
}

void AGamePlayPC::ServerBuyAK47_Implementation()
{
	AFPSCharacter* pCharacter = Cast<AFPSCharacter>(GetPawn());
	if (pCharacter)
	{
		// 스폰시키기
		// 스폰위치
		FVector SpawnedLocation = pCharacter->GetActorLocation() + pCharacter->GetActorForwardVector() * 100;

		// pCharacter의 회전 값을 가져옵니다.
		FRotator SpawnedRotation = pCharacter->GetActorRotation();

		AAK47* PCAK47 = GetWorld()->SpawnActor<AAK47>(AK47Class, SpawnedLocation, SpawnedRotation);

	}
}

void AGamePlayPC::ServerBuyM4_Implementation()
{
	AFPSCharacter* pCharacter = Cast<AFPSCharacter>(GetPawn());
	if (pCharacter)
	{
		// 스폰시키기
		// 스폰위치
		FVector SpawnedLocation = pCharacter->GetActorLocation() + pCharacter->GetActorForwardVector() * 100;
	
		// pCharacter의 회전 값을 가져옵니다.
		FRotator SpawnedRotation = pCharacter->GetActorRotation();
	
		AM4* PCM4 = GetWorld()->SpawnActor<AM4>(M4Class, SpawnedLocation, SpawnedRotation);
	
	}
}

void AGamePlayPC::ServerBuyMag_Implementation()
{
	AFPSCharacter* pCharacter = Cast<AFPSCharacter>(GetPawn());
	if (pCharacter)
	{
		// 스폰시키기
		// 스폰위치
		FVector SpawnedLocation = pCharacter->GetActorLocation() + pCharacter->GetActorForwardVector();

		// pCharacter의 회전 값을 가져옵니다.
		FRotator SpawnedRotation = pCharacter->GetActorRotation();

		AItemBase* PCMag = GetWorld()->SpawnActor<AItemBase>(MagClass, SpawnedLocation, SpawnedRotation);

	}
}

void AGamePlayPC::ServerBuyMedItem_Implementation()
{
	AFPSCharacter* pCharacter = Cast<AFPSCharacter>(GetPawn());
	if (pCharacter)
	{
		// 스폰시키기
		// 스폰위치
		FVector SpawnedLocation = pCharacter->GetActorLocation() + pCharacter->GetActorForwardVector();

		// pCharacter의 회전 값을 가져옵니다.
		FRotator SpawnedRotation = pCharacter->GetActorRotation();

		AItemBase* PCMedItem = GetWorld()->SpawnActor<AItemBase>(MedItemClass, SpawnedLocation, SpawnedRotation);

	}
}
