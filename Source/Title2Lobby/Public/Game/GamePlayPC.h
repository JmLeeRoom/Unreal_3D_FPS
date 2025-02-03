// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayPC.generated.h"

/**
 * 
 */
UCLASS()
class TITLE2LOBBY_API AGamePlayPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	// 무기를 구매했을 때 서버에 알리는 함수
	UFUNCTION(Server, Reliable)
	void ServerBuyPistol();

	UFUNCTION(Server, Reliable)
	void ServerBuyThompson();

	UFUNCTION(Server, Reliable)
	void ServerBuyAK47();

	UFUNCTION(Server, Reliable)
	void ServerBuyM4();

	UFUNCTION(Server, Reliable)
	void ServerBuyMag();

	UFUNCTION(Server, Reliable)
	void ServerBuyMedItem();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AWeaponBase> PistolClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AWeaponBase> ThompsonClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AWeaponBase> AK47Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AWeaponBase> M4Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AItemBase> MagClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AItemBase> MedItemClass;
};
