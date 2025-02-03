// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemInterface.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class TITLE2LOBBY_API AFPSCharacter : public ACharacter, public IItemInterface
{
	GENERATED_BODY()
protected:
	// 1인칭 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="FPSCamera")
	UCameraComponent* FirstPersonCamera;

	// 키입력
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* FireInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PickUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* StoreOpenAction;
public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION(BlueprintCallable)
	void GetDamage(float Damage);

protected:
	// 키입력 함수
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartFire(const FInputActionValue& Value);
	void StopFire(const FInputActionValue& Value);
	/// 추가 /// 
	void PickUp(const FInputActionValue& Value);
	void Reload(const FInputActionValue& Value);
	void Drop(const FInputActionValue& Value);
	void StoreOpen(const FInputActionValue& Value);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	// 서버에서 실행될 발사 로직
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();
	bool ServerFire_Validate();
	void ServerFire_Implementation();

public:
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(TSubclassOf<class AWeaponBase> WeaponClass);

	UFUNCTION()
	void WeaponSetOwner();

	UFUNCTION(BlueprintCallable)
	void StoreUIOpen();

	UFUNCTION(BlueprintCallable)
	void StoreUIClose();


	AActor* FindNearestWeapon();

	UPROPERTY(BlueprintReadWrite)
	AActor* m_EquipWeapon;

	UPROPERTY(BlueprintReadWrite)
	AWeaponBase* m_WeaponBase;

	FTimerHandle WeaponSetOwnerTimer;

	UPROPERTY(BlueprintReadWrite)
	bool IsStoreOpen = false;


public:
	//네트워크 코드 영역
	UFUNCTION(Server, Reliable)
	void ReqPickUp();

	UFUNCTION(NetMulticast, Reliable)
	void ResPickUp(AActor* PickUpActor);

	UFUNCTION(Client, Reliable)
	void ResPressFClient();

	UFUNCTION(Server, Reliable)
	void ReqTrigger(bool IsPress);

	UFUNCTION(NetMulticast, Reliable)
	void ResTrigger(bool IsPress);

	UFUNCTION(Server, Reliable)
	void ReqReload();

	UFUNCTION(NetMulticast, Reliable)
	void ResReload();

	UFUNCTION(Server, Reliable)
	void ReqDrop();

	UFUNCTION(NetMulticast, Reliable)
	void ResDrop();

public:
	//ItemInterface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EventGetItem(EItemType itemType);

	void EventGetItem_Implementation(EItemType itemType) override;

	
};
