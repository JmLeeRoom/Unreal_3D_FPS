// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class TITLE2LOBBY_API UStoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInfo", meta = (BindWidget))
	class UTextBlock* GoldLackText;

	UPROPERTY(EditAnywhere, Category = "TextAnim", meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FailedTextAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USoundBase* BuySound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USoundBase* FailedSound;


public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void BuyButton_Pistol();

	UFUNCTION(BlueprintCallable)
	void BuyButton_Thompson();

	UFUNCTION(BlueprintCallable)
	void BuyButton_AK47();

	UFUNCTION(BlueprintCallable)
	void BuyButton_M4();

	UFUNCTION(BlueprintCallable)
	void BuyButton_Med();

	UFUNCTION(BlueprintCallable)
	void BuyButton_Ammo();

public:
	// 소환될 무기 클래스
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AWeaponBase> PistolClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AWeaponBase> ThompsonClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AWeaponBase> AK47Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AWeaponBase> M4Class;
public:
	// 아이템클래스
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AItemBase> MedClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AItemBase> AmmoClass;

};
