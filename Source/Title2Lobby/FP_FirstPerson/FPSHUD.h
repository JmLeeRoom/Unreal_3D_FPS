// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class TITLE2LOBBY_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	// 최종에서는
	// crosshiar 추가
public:
	// To add mapping context
	virtual void BeginPlay() override;
	
public:
	void BindMyPlayerState();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyHp(float CurHp, float MaxHp);

	void OnUpdateMyHp_Implementation(float CurHp, float MaxHp);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyAmmo(int Ammo);

	void OnUpdateMyAmmo_Implementation(int Ammo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyGold(int Gold);

	void OnUpdateMyGold_Implementation(int Gold);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyMag(int Mag);

	void OnUpdateMyMag_Implementation(int Mag);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HudWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* HudWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> StoreHudWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* StoreWidget;

	FTimerHandle th_BindMyPlayerState;
};
