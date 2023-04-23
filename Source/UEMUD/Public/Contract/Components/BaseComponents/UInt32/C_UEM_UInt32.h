// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "C_UEM_UInt32.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_UInt32: public FCF_Component 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Value = 0;

	FC_UEM_UInt32()
	{
		Value = 0;
	}

	FC_UEM_UInt32(int32 _Value)
	{
		Value = _Value;
	}
	
};
