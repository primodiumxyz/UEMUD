// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "C_UEM_MudEntityIdMapping.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_MudEntityIdMapping : public FCF_Component
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TMap<FString,int32> MudEntityIdToLocalContextId = TMap<FString,int32>();
	

	FC_UEM_MudEntityIdMapping()
	{
		MudEntityIdToLocalContextId = TMap<FString,int32>();
	}
};
