// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Contract/Tables/ParsedTable.h"
#include "DS_UEM_MudTableConfig.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Mud Table Config")) // Give it a better looking name in UI
class UEMUD_API UDS_UEM_MudTableConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config,EditAnywhere,BlueprintReadOnly)
	FString SourceDirSubDir = "Mudv2ExampleProject/TableDefinitions/";

	UPROPERTY(Config,EditAnywhere,BlueprintReadOnly)
	FString ClassModuleAPIMacro;
	
	
	UPROPERTY(Config,EditAnywhere,BlueprintReadOnly)
	TArray<FParsedTable> Tables = TArray<FParsedTable>();

	UPROPERTY(Config,EditAnywhere,BlueprintReadOnly)
	FString TableComponentHeaderPath;

	UPROPERTY(Config,EditAnywhere,BlueprintReadOnly)
	FString TableComponentCppPath;
	
	UPROPERTY(Config,EditAnywhere,BlueprintReadOnly)
	TMap<EValueTypeSchema,FString> ValueTypeTemplatePaths;

	
	
};
