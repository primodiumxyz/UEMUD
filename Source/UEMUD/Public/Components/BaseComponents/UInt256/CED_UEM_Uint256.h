// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CED_UEM_ComponentBase.h"
#include "UObject/Object.h"
#include "CED_UEM_Uint256.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class UEMUD_API UCED_UEM_Uint256 : public UCED_UEM_ComponentBase
{
	GENERATED_BODY()
protected:
	virtual FInstancedStruct GetInitializedComponentInstancedStruct() override;
	
public:
	

	virtual FInstancedStruct GetComponentFromEncodedData(const TArray<uint8>& EncodedValues) override;
	
};
