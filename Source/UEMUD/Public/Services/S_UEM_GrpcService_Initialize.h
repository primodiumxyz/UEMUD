// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurboLinkGrpcClient.h"
#include "UObject/Object.h"
#include "S_UEM_GrpcService_Initialize.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API US_UEM_GrpcService_Initialize : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual FString GetEndPointName();

	
};
