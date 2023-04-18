// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/S_UEM_GrpcService_Initialize.h"
#include "UObject/Object.h"
#include "S_UEM_ECSStateSnapShotService_Initialize.generated.h"


UCLASS()
class UEMUD_API US_UEM_ECSStateSnapShotService_Initialize : public US_UEM_GrpcService_Initialize
{
	GENERATED_BODY()

public:



	

	virtual FString GetEndPointName() override;


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;



	UFUNCTION()
	void On_ECSStateSnapshotService_StateChanged(EGrpcServiceState NewState) ;
	

	

};
