// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Beretta.h"

ABeretta::ABeretta()
{
	KindOfWeapon = EWeaponType::Beretta;
	m_Ammo = 15;
	WeaponPrice = 500;
	bReplicates = true;
}
