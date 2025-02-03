// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"
#include "FP_FirstPerson/FPSHUD.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h" // DOREPLIFETIME ����� ���� ������� �߰�
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
AWeaponBase::AWeaponBase() :m_Ammo(30)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	WeaponMesh->SetCollisionProfileName("Weapon");
	WeaponMesh->SetSimulatePhysics(true);
	SetRootComponent(WeaponMesh);

	WeaponMuzzleFlashComp = CreateDefaultSubobject<UNiagaraComponent>("N_MuzzleFlash");
	WeaponMuzzleFlashComp->SetupAttachment(WeaponMesh, "Muzzle");
	WeaponMuzzleFlashComp->bAutoActivate = false;
	bReplicates = true;
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponBase, m_Ammo);
}

void AWeaponBase::EventTrigger_Implementation(bool IsPress)
{
	if (false == IsPress)
	{
		return;
	}
	if (m_Ammo == 0)
	{
		return;
	}

	m_pOwnChar->PlayAnimMontage(ShootMontage);
}

void AWeaponBase::EventShoot_Implementation()
{
	if (false == IsCanShoot())
	{
		return;
	}

	// 총구화염 나이아가라
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFire, WeaponMesh->GetSocketLocation("Muzzle"));

	WeaponMuzzleFlashComp->Deactivate();

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WeaponSoundBase,
		WeaponMesh->GetSocketLocation("Muzzle"));

	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (pPlayer0 != m_pOwnChar->GetController())
	{
		return;
	}


	FVector vStart = WeaponMesh->GetSocketLocation("Muzzle");
	FVector vEnd = vStart + WeaponMesh->GetForwardVector() * 10000.0f;

	ReqShoot(vStart, vEnd);
}

void AWeaponBase::EventReload_Implementation()
{
	// Activate reload delay
	if (m_Ammo == 30)
	{
		return;
	}
	m_pOwnChar->PlayAnimMontage(ReloadMontage);

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WeaponReloadSoundBase, WeaponMesh->GetSocketLocation("Muzzle"));
	//GetWorldTimerManager().SetTimer(TimerHandle_ReloadDelay, this, &AWeaponBase::EventReload, 2.f, false);
}

void AWeaponBase::EventPickUp_Implementation(ACharacter* pOwnChar)
{
	m_pOwnChar = pOwnChar;
	//m_pOwnChar->bUseControllerRotationYaw = true;
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetCollisionProfileName("NoCollision");
	WeaponMesh->AttachToComponent(pOwnChar->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");

	OnUpdateAmmoToHud(m_Ammo);
}

void AWeaponBase::EventResetAmmo_Implementation()
{

	if (KindOfWeapon == EWeaponType::Beretta)
	{
		SetAmmo(15);
	}
	else
	SetAmmo(30);
}

void AWeaponBase::EventDrop_Implementation(ACharacter* PlayerOwnChar)
{
	OnUpdateAmmoToHud(0);
	WeaponMesh->SetCollisionProfileName("Weapon");
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	WeaponMesh->SetSimulatePhysics(true);
	//m_pOwnChar->bUseControllerRotationYaw = false;
	// ���� ������ ����������
	if (KindOfWeapon == EWeaponType::Beretta)
	{
		WeaponMesh->AddImpulse(PlayerOwnChar->GetActorForwardVector() * 500.0f);
	}
	else
	{
		WeaponMesh->AddImpulse(PlayerOwnChar->GetActorForwardVector() * 2000.0f);
	}

	m_pOwnChar = nullptr;
}

float AWeaponBase::GetFireStartLength()
{
	if (false == IsValid(m_pOwnChar))
		return 0.0f;

	USpringArmComponent* pArm = Cast<USpringArmComponent>(m_pOwnChar->GetComponentByClass(USpringArmComponent::StaticClass()));
	if (false == IsValid(pArm))
		return 0.0f;

	return pArm->TargetArmLength + 100;
}

bool AWeaponBase::IsCanShoot()
{
	if (m_Ammo <= 0)
		return false;

	return true;
}

bool AWeaponBase::UseAmmo()
{
	if (false == IsCanShoot())
		return false;

	m_Ammo = m_Ammo - 1;
	m_Ammo = FMath::Clamp(m_Ammo, 0, 30);

	OnRep_Ammo();

	return true;
}

void AWeaponBase::SetAmmo(int Ammo)
{
	m_Ammo = Ammo;

	OnRep_Ammo();
}

void AWeaponBase::OnUpdateAmmoToHud(int Ammo)
{
	if (nullptr == m_pOwnChar)
		return;

	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (m_pOwnChar->GetController() != pPlayer0)
		return;

	AFPSHUD* pHud = Cast<AFPSHUD>(pPlayer0->GetHUD());
	if (nullptr == pHud)
		return;

	pHud->OnUpdateMyAmmo(Ammo);
}

void AWeaponBase::OnRep_Ammo()
{
	OnUpdateAmmoToHud(m_Ammo);
}

void AWeaponBase::ReqShoot_Implementation(FVector vStart, FVector vEnd)
{
	if (false == UseAmmo())
		return;

	//->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("ReqShoot_Implementation"));

	FHitResult result;
	FCollisionObjectQueryParams collisionObjParams;
	collisionObjParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	collisionObjParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	collisionObjParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	collisionObjParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	collisionObjParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Vehicle);
	collisionObjParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Destructible);

	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(m_pOwnChar);

	bool isHit = GetWorld()->LineTraceSingleByObjectType(result, vStart, vEnd, collisionObjParams, collisionParams);
	DrawDebugLine(GetWorld(), vStart, vEnd, FColor::Red, false, 1.0f);

	if (false == isHit)
		return;

	ACharacter* pHitChar = Cast<ACharacter>(result.GetActor());
	if (false == IsValid(pHitChar))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Nohit")));
		return;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("HitChar = %s"), *pHitChar->GetName()));

	UGameplayStatics::ApplyDamage(pHitChar, WeaponDamage, m_pOwnChar->GetController(), this, UDamageType::StaticClass());
}

