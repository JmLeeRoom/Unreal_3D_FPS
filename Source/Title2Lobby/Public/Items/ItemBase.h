// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "ItemBase.generated.h"

class UParticleSystemComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class TITLE2LOBBY_API AItemBase : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* ItemNiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* ItemNiagaraVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* UsingItemNiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* UsingItemVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType EnumItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoItemPrice = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MedItemPrice = 150;


};
