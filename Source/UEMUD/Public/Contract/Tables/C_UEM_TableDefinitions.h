// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core\Component\CF_Component.h"
#include "C_UEM_TableDefinitions.generated.h"

USTRUCT()
struct UEMUD_API FC_UEM_TableDefinitions : public FCF_Component
{

	
	GENERATED_BODY()
	
	FC_UEM_TableDefinitions() = default;

	explicit FC_UEM_TableDefinitions(const TMap<FString, UScriptStruct*>& TableDefinitions)
		: TableDefinitions(TableDefinitions)
	{
		
	}


	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TMap<FString,UScriptStruct*> TableDefinitions = TMap<FString,UScriptStruct*>();

	
};
