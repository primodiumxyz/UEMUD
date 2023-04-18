// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurboLinkGrpcClient.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "C_UEM_GrpcContext.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_GrpcContext : public FCF_Component
{
	GENERATED_BODY()
public:

	
	UPROPERTY(BlueprintReadOnly)
	FGrpcContextHandle GrpcContextHandle;
	


	FC_UEM_GrpcContext()
	{
	}

	FC_UEM_GrpcContext(FGrpcContextHandle _GrpcContextHandle)
	{
		GrpcContextHandle = _GrpcContextHandle;
	}

	
	
};