// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CED_UEM_ComponentBase.h"
#include "Systems/SED_UEM_Base.h"
#include "UObject/Object.h"
#include "DA_UEM_ComponentMappings.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UEMUD_API UDA_UEM_ComponentMappings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<TSubclassOf<UCED_UEM_ComponentBase>> MappedComponents;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<TSubclassOf<USED_UEM_Base>> MappedSystems;
	
};
