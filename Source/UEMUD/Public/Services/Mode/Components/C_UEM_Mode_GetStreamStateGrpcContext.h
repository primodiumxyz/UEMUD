// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core\Component\CF_Component.h"
#include "Services/Components/C_UEM_GrpcContext.h"
#include "C_UEM_Mode_GetStreamStateGrpcContext.generated.h"



USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_Mode_GetStreamStateGrpcContext : public FC_UEM_GrpcContext
{
	GENERATED_BODY()
public:
	
	FC_UEM_Mode_GetStreamStateGrpcContext()
	{
		
	}

	FC_UEM_Mode_GetStreamStateGrpcContext(FGrpcContextHandle _Mode_GetStreamStateGrpcGrpcContextHandle)
	{
		GrpcContextHandle = _Mode_GetStreamStateGrpcGrpcContextHandle;
	}
	
};