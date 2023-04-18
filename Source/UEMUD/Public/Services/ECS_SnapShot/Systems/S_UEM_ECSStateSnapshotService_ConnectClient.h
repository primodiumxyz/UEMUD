// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "S_UEM_ECSStateSnapshotService_ConnectClient.generated.h"



UCLASS()
class UEMUD_API US_UEM_ECSStateSnapshotService_ConnectClient : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnECSStateSnapshotServiceStateChanged(FM_UEM_OnECSStateSnapshotService_StateChanged OnECSStateSnapshotServiceStateChanged);

	UFUNCTION()
	void OnECSStateSnapshotServiceResponse(FGrpcContextHandle Handle, const FGrpcResult& Result, const FGrpcEcssnapshotECSStateReply& Response);
};
