// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core\Component\CF_Component.h"
#include "C_UEM_Coord.generated.h"

USTRUCT()
struct UEMUD_API FC_UEM_Coord : public FCF_Component
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 x = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 y = 0;

	FC_UEM_Coord()
	{
		x = 0;
		y = 0;
	}

	FC_UEM_Coord(int32 _x, int32 _y)
	{
		x = _x;
		y = _y;
	}
};
