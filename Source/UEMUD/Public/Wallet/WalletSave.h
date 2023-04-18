// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/Object.h"
#include "WalletSave.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UEMUD_API UWalletSave : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	TArray<uint8> WalletPrivateKey;
};
