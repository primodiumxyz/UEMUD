// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "C_UEM_Bool.generated.h"




USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_Bool: public FCF_Component 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Value = false;

	FC_UEM_Bool()
	{
		Value = false;
	}

	FC_UEM_Bool(bool _Value)
	{
		Value = _Value;
	}
	
};
