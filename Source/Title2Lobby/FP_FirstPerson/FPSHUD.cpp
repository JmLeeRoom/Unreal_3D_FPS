// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHUD.h"

#include "FPSPlayerState.h"
#include "Blueprint/UserWidget.h"
// 로직은 블루프린트에서 최대한 
void AFPSHUD::BeginPlay()
{
	Super::BeginPlay();
	check(HudWidgetClass);

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	StoreWidget = CreateWidget<UUserWidget>(GetWorld(), StoreHudWidgetClass);
	StoreWidget->AddToViewport();
	StoreWidget->SetVisibility(ESlateVisibility::Hidden);

	HudWidget->AddToViewport();

	BindMyPlayerState();
}

void AFPSHUD::BindMyPlayerState()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("pc"));
	if (IsValid(pc))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("IsValid(pc)"));
		AFPSPlayerState* ps = Cast<AFPSPlayerState>(pc->PlayerState);
		if (IsValid(ps))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("IsValid(ps)"));
			ps->m_Dele_UpdateHp.AddDynamic(this, &AFPSHUD::OnUpdateMyHp);
			OnUpdateMyHp(ps->m_CurHp, 100);

			
			ps->m_Dele_UpdateAmmo.AddDynamic(this, &AFPSHUD::OnUpdateMyAmmo);
			OnUpdateMyAmmo(ps->m_Ammo);
			
			ps->m_Dele_UpdateGold.AddDynamic(this, &AFPSHUD::OnUpdateMyGold);
			OnUpdateMyGold(ps->m_Gold);
			
			ps->m_Dele_UpdateMag.AddDynamic(this, &AFPSHUD::OnUpdateMyMag);
			OnUpdateMyMag(ps->m_Mag);

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("AShootingHUD Bind Success!"));
			return;
		}
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(th_BindMyPlayerState, this, &AFPSHUD::BindMyPlayerState, 0.01f, false);
}

void AFPSHUD::OnUpdateMyHp_Implementation(float CurHp, float MaxHp)
{
}

void AFPSHUD::OnUpdateMyAmmo_Implementation(int Ammo)
{
}

void AFPSHUD::OnUpdateMyGold_Implementation(int Gold)
{
}

void AFPSHUD::OnUpdateMyMag_Implementation(int Mag)
{
}
