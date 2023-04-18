// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Endpoints/RpcCall.h"
#include "Ethereum/GetBalance/Messages/M_UEM_GetBalanceRequest.h"

#include "UObject/Object.h"
#include "S_UEM_GetBalance.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API US_UEM_GetBalance : public UGameInstanceSubsystem
{
	GENERATED_BODY()



	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnGetBalanceRequest(FM_UEM_GetBalanceRequest GetBalanceRequest) const;
	

	
};
