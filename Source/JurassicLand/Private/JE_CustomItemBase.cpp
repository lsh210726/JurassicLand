// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_CustomItemBase.h"

UJE_CustomItemBase::UJE_CustomItemBase()
{

}

UJE_CustomItemBase* UJE_CustomItemBase::CreateItemCopy()
{
	UJE_CustomItemBase* ItemCopy = CreateDefaultSubobject<UJE_CustomItemBase>(TEXT("Item"));

	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemTextData = this->ItemTextData;
	ItemCopy->ItemAssetsData = this->ItemAssetsData;

	return ItemCopy;
}

void UJE_CustomItemBase::Use(ABlueTrex* character)
{

}
