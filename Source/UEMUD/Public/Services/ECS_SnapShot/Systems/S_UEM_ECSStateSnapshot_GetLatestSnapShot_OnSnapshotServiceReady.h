// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "S_UEM_ECSStateSnapshot_GetLatestSnapShot_OnSnapshotServiceReady.generated.h"


UCLASS()
class UEMUD_API US_UEM_ECSStateSnapshot_GetLatestSnapShot_OnSnapshotServiceReady : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnECSStateSnapshotGrpcContextComponentSet(const FCF_ComponentSetMessageBase ECSStreamGrpcContextComponentSet);

	UFUNCTION(BlueprintCallable)
	void GetLatestSnapShot();
};
