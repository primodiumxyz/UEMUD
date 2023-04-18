// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/S_UEM_GrpcService_Initialize.h"
#include "UObject/Object.h"
#include "SFaucet/FaucetService.h"
#include "S_UEM_FaucetServiceHandler.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API US_UEM_FaucetServiceHandler : public US_UEM_GrpcService_Initialize
{
	GENERATED_BODY()

public:


	UPROPERTY()
	UFaucetServiceClient* FaucetServiceClient;

	UPROPERTY()
	UFaucetService* FaucetService;

	UPROPERTY()
	FGrpcContextHandle FaucetGrpcContextHandle;

	
	virtual FString GetEndPointName() override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION()
	void On_FaucetService_StateChanged(EGrpcServiceState NewState);

	UFUNCTION()
	void SubscribeToFaucet();

	UFUNCTION()
	void RequestDripDev(FString WalletAddress);

	UFUNCTION()
	void On_RequestDripDev_Response(FGrpcContextHandle Handle, const FGrpcResult& Result, const FGrpcFaucetDripResponse& Response);


	UFUNCTION()
	void OnFaucetServiceRequestDripDev(FM_UEM_FaucetServiceRequestDripDev FM_UEM_FaucetServiceRequestDripDev);


};
