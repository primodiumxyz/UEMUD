// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ContractEncoderDecoder_UEM_Base.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UEMUD_API UContractEncoderDecoder_UEM_Base : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString Id;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString ContractAddress;
	

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString ComponentContractAbi = "";


	UFUNCTION(BlueprintCallable)
	FString GetIdHex() const;

	
};
