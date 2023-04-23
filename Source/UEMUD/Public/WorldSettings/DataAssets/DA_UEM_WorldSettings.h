// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Contract/Components/DA_UEM_ComponentMappings.h"
#include "UObject/Object.h"
#include "DA_UEM_WorldSettings.generated.h"

/**
 * 
 */



UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Mud World Settings")) // Give it a better looking name in UI
class UEMUD_API UDA_UEM_WorldSettings : public UDeveloperSettings
{

	
public:
	GENERATED_BODY()

	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	FString WorldContractAddress;

	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	FString JsonRPCUrl;

	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	FString ChainId;

	
	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	TSoftObjectPtr<UDA_UEM_ComponentMappings> ComponentMappings;
	
	
};
