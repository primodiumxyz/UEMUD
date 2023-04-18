// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ethereum/SendRawTransaction/Messages/M_UEM_SendRawTransactionRequest.h"
#include "S_UEM_SendRawTransaction.generated.h"


UCLASS()
class UEMUD_API US_UEM_SendRawTransaction : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnSendRawTransactionRequest(FM_UEM_SendRawTransactionRequest SendRawTransactionCountRequest) const;

	
	
};
