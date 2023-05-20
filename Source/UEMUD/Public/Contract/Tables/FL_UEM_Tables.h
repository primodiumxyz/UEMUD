// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParsedTable.h"
#include "UObject/Object.h"
#include "FL_UEM_Tables.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API UFL_UEM_Tables : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()



	UFUNCTION(BlueprintCallable)
	static EValueTypeSchema GetValueType(FString SolidityType)
	{
		if(SolidityType.Contains("int"))
			return EValueTypeSchema::Number;
		else if(SolidityType.Equals("bool"))
			return EValueTypeSchema::Bool;
		else if(SolidityType.Equals("string"))
			return EValueTypeSchema::String;
		else if(SolidityType.Equals("address"))
			return EValueTypeSchema::String;
		
		return EValueTypeSchema::Uint256;
	}

	
};
