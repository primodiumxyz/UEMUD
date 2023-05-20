// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "S_UEM_ModeService_ConnectClient.generated.h"



UCLASS()
class UEMUD_API US_UEM_ModeService_ConnectClient : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnModeServiceStateChanged(FM_UEM_OnModeService_StateChanged OnModeServiceStateChanged);

	UFUNCTION()
	void OnModeService_GetStreamStateResponse(FGrpcContextHandle Handle, const FGrpcResult& Result, const FGrpcModeQueryLayerStateStreamResponse& Response);

	UFUNCTION()
	void OnModeService_GetStateResponse(FGrpcContextHandle Handle, const FGrpcResult& Result, const FGrpcModeQueryLayerStateResponse& Response);


	 int32 GetContextIdForEntityId(FString EntityId) const;
};
