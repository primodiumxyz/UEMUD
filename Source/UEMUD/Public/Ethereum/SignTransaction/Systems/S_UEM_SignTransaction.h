// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "S_UEM_SignTransaction.generated.h"


UCLASS()
class UEMUD_API US_UEM_SignTransaction : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnSignTransactionRequest(FM_UEM_SignTransactionRequest GetBalanceRequest) const;

	
	UFUNCTION()
	void OnSignTransactionResponse(
		const bool  bSuccess ,
		FString ErrorMessage,
	   FString SignedTransaction ,
	   FString  MessageHash ,
	   FString TransactionHash) const;
	
};
