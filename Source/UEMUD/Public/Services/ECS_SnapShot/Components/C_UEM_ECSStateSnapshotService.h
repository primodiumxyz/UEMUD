// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "TurboLinkGrpcClient.h"
#include "SEcsstream/EcsStreamService.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "SEcssnapshot/EcsSnapshotService.h"
#include "C_UEM_ECSStateSnapshotService.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_ECSStateSnapshotService : public FCF_Component
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadOnly)
	UECSStateSnapshotService* ECSStateSnapshotService;
	


	FC_UEM_ECSStateSnapshotService()
	{
		ECSStateSnapshotService = nullptr;
	}

	FC_UEM_ECSStateSnapshotService(UECSStateSnapshotService* _ECSStateSnapshotService)
	{
		ECSStateSnapshotService = _ECSStateSnapshotService;
	}

	
	
};
