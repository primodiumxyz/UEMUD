// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../Messages/M_UEM_OnECSStreamService_StateChanged.h"
#include "S_UEM_ECSStreamService_ConnectClient.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API US_UEM_ECSStreamService_ConnectClient : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnECSServiceStateChanged(FM_UEM_OnECSStreamService_StateChanged M_UEM_OnECSServiceStateChanged);

	UFUNCTION()
	void OnECSStreamServiceResponse(FGrpcContextHandle Handle, const FGrpcResult& Result, const FGrpcEcsstreamECSStreamBlockBundleReply& Response);
};
