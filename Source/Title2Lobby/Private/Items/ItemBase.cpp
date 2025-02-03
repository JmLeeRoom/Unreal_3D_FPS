// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));

	SetRootComponent(SceneComp);
	ItemStaticMesh->SetupAttachment(RootComponent);
	ItemStaticMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	ItemNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("N_ItemVFX");
	ItemNiagaraComponent->SetupAttachment(ItemStaticMesh);
	ItemNiagaraComponent->bAutoActivate = true;

	UsingItemNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("N_UsingItemVFX");
	UsingItemNiagaraComponent->SetupAttachment(ItemStaticMesh);
	UsingItemNiagaraComponent->bAutoActivate = false;

	bReplicates = true;
	SetReplicateMovement(true);

	ItemStaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemBeginOverlap);

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ItemStaticMesh->AddRelativeRotation(FRotator(0.0f, 1.0f, 0.0f));
}

void AItemBase::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IItemInterface* ItemInterface = Cast<IItemInterface>(OtherActor);
	if (ItemInterface)
	{
		ItemInterface->Execute_EventGetItem(OtherActor, EnumItemType);
		// 나이아가라 스폰
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), UsingItemVFX, ItemStaticMesh->GetComponentLocation());
		Destroy();
	}
}

