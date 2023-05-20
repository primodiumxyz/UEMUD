// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core\Component\CF_Component.h"
#include "CCM_UEM_Base.generated.h"

USTRUCT()
struct UEMUD_API FCCM_UEM_Base : public FCF_Component
{
	

	GENERATED_BODY()

public:


	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ContractId = "";
	
	FCCM_UEM_Base() = default;

	explicit FCCM_UEM_Base(const FString& ContractId)
		: ContractId(ContractId)
	{
	}

	

	
	
};
