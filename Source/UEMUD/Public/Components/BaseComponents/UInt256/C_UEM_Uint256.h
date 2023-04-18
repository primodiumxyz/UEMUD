// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "C_UEM_Uint256.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_Uint256 : public FCF_Component
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TArray<uint8> Value = TArray<uint8>();


	FC_UEM_Uint256()
	{
		Value = TArray<uint8>();
	}

	FC_UEM_Uint256(const TArray<uint8>& _Value)
	{
		Value = _Value;
	}
	
	
};
