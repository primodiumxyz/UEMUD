// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "S_UEM_EstimateGas.generated.h"

UCLASS()
class UEMUD_API US_UEM_EstimateGas : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnEstimateGasRequest(FM_UEM_EstimateGasRequest GetBalanceRequest) const;

	
};
