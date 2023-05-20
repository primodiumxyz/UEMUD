// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core\Component\CF_Component.h"
#include "Services/Components/C_UEM_GrpcContext.h"
#include "C_UEM_Mode_GetStateGrpcContext.generated.h"



USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_Mode_GetStateGrpcContext : public FC_UEM_GrpcContext
{
	GENERATED_BODY()
public:
	
	FC_UEM_Mode_GetStateGrpcContext()
	{
		
	}

	FC_UEM_Mode_GetStateGrpcContext(FGrpcContextHandle _Mode_GetStateGrpcGrpcContextHandle)
	{
		GrpcContextHandle = _Mode_GetStateGrpcGrpcContextHandle;
	}
	
};