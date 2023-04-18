// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "Contract/ContractEncoderDecoder_UEM_Base.h"
#include "UObject/Object.h"
#include "CED_UEM_ComponentBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UEMUD_API UCED_UEM_ComponentBase : public UContractEncoderDecoder_UEM_Base
{
	GENERATED_BODY()
protected:

	UFUNCTION()
	virtual FInstancedStruct GetInitializedComponentInstancedStruct();

public:

	
	UFUNCTION()
	virtual FInstancedStruct GetComponentFromEncodedData(const TArray<uint8>& EncodedValues);

	

};
