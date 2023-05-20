// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "UObject/Object.h"
#include "ParsedTable.generated.h"


UENUM(BlueprintType)
enum class EValueTypeSchema : uint8 {
	Number = 0 UMETA(DisplayName = "Number"),
	Bool = 1  UMETA(DisplayName = "Bool"),
	String = 2     UMETA(DisplayName = "String"),
	Uint256 = 3 UMETA(DisplayName = "Uint256"),
	Address = 4     UMETA(DisplayName = "Address"),
	Bytes = 5    UMETA(DisplayName = "Bytes"),
};




USTRUCT(BlueprintType)
struct UEMUD_API FParsedTableElement 
{
	FParsedTableElement( const FString& Name, const EValueTypeSchema Type)
		: Type(Type),
		  Name(Name)
	{
	}

	FParsedTableElement() = default;
	GENERATED_BODY()


	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TEnumAsByte<EValueTypeSchema> Type;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString Name = "";
	
};


USTRUCT(BlueprintType)
struct UEMUD_API FParsedTable 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString TableId = "";

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FParsedTableElement> Elements = TArray<FParsedTableElement>();
	
};

USTRUCT(BlueprintType)
struct UEMUD_API FParsedConfig 
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FParsedTable> Tables = TArray<FParsedTable>();
	
};


USTRUCT(BlueprintType)
struct UEMUD_API FTableElementResult 
{
	FTableElementResult() = default;

	FTableElementResult(const FString& Key, const TArray<FString>& Values)
		: Key(Key),
		  Values(Values)
	{
	}

	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString Key = "";

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TArray<FString> Values = TArray<FString>();
	
	
};
