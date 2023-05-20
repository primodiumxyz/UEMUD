// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Contract/Tables/ParsedTable.h"
#include "UObject/Object.h"
#include "ParseConfig.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API UParseConfig : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "MUD")
	static void ParseConfigString(FString Config, FParsedConfig& ParsedConfig, const UObject* WorldContextObject);
};
