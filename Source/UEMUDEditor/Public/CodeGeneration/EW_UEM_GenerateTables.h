// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "UObject/Object.h"
#include "EW_UEM_GenerateTables.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class UEMUDEDITOR_API UEW_UEM_GenerateTables : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(CallInEditor,BlueprintCallable)
	static void GenerateTables();


	

	
};
