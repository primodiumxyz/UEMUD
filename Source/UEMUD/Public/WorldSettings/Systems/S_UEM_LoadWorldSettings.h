// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UEMUD/Public/Contract/Components/DA_UEM_ComponentMappings.h"
#include "S_UEM_LoadWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API US_UEM_LoadWorldSettings : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UDA_UEM_ComponentMappings* ComponentMappings;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
