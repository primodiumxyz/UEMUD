

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "SEcsstream/EcsStreamClient.h"
#include "UObject/Object.h"
#include "SEcssnapshot/EcsSnapshotClient.h"
#include "C_UEM_ECSStateSnapshotServiceClient.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_ECSStateSnapshotServiceClient : public FCF_Component
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	UECSStateSnapshotServiceClient* ECSStateSnapshotServiceClient;

	
	FC_UEM_ECSStateSnapshotServiceClient()
	{
		ECSStateSnapshotServiceClient = nullptr;
	}

	FC_UEM_ECSStateSnapshotServiceClient(UECSStateSnapshotServiceClient* _ECSStateSnapshotServiceClient)
	{
		ECSStateSnapshotServiceClient = _ECSStateSnapshotServiceClient;
	}

	
};