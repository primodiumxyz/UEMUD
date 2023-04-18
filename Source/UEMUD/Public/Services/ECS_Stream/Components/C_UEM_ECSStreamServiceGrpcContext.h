// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "Services/Components/C_UEM_GrpcContext.h"
#include "UObject/Object.h"
#include "C_UEM_ECSStreamServiceGrpcContext.generated.h"





USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_ECSStreamServiceGrpcContext : public FC_UEM_GrpcContext
{
	GENERATED_BODY()
public:

	


	FC_UEM_ECSStreamServiceGrpcContext()
	{
		
	}

	FC_UEM_ECSStreamServiceGrpcContext(FGrpcContextHandle _ECSStreamServiceGrpcContextHandle)
	{
		GrpcContextHandle = _ECSStreamServiceGrpcContextHandle;
	}

	
	
};