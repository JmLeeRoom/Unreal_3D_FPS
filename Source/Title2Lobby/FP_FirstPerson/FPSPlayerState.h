// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FPSPlayerState.generated.h"

/**
 * 
 */
class ACharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_UpdateHp, float, CurHp, float, MaxHp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateAmmo, int, Ammo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateGold, int, Gold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateMag, int, Mag);
UCLASS()
class TITLE2LOBBY_API AFPSPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	AFPSPlayerState();
public:
	UFUNCTION()
	void AddDamage(float Damage);

	UFUNCTION()
	void AddHeal(float Heal);

	UFUNCTION()
	void SetAmmo(int32 _Ammo);

	UFUNCTION()
	void UseAmmo(int32 _Ammo);

	UFUNCTION()
	void SetMag(int32 M_Mag);

	UFUNCTION()
	void AddMag();

	UFUNCTION()
	void UseMag();
	
	UFUNCTION(BlueprintCallable)
	void SetGold(int32 _Gold);

	
public:
	UFUNCTION()
	void OnRep_CurHp();

	UFUNCTION()
	void OnRep_Ammo();

	UFUNCTION()
	void OnRep_Gold();

	UFUNCTION()
	void OnRep_Mag();
public:
	UPROPERTY(ReplicatedUsing = OnRep_CurHp)
	float m_CurHp;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateHp m_Dele_UpdateHp;

	UPROPERTY(ReplicatedUsing = OnRep_Ammo)
	float m_Ammo;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateAmmo m_Dele_UpdateAmmo;

	UPROPERTY(ReplicatedUsing = OnRep_Gold)
	float m_Gold;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateGold m_Dele_UpdateGold;

	UPROPERTY(ReplicatedUsing = OnRep_Mag)
	float m_Mag;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateMag m_Dele_UpdateMag;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* m_pOwnChar;
};
