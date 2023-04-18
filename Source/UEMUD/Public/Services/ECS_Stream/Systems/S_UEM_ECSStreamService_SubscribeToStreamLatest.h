// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/Messages/ComponentSet/CF_ComponentSetMessage.h"
#include "UObject/Object.h"
#include "S_UEM_ECSStreamService_SubscribeToStreamLatest.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API US_UEM_ECSStreamService_SubscribeToStreamLatest : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnRequestSubscribeToWorldStream(FM_UEM_ECSStream_RequestSubscribeToWorldStream RequestSubscribeToWorldStream);


	UFUNCTION()
	void OnECSStreamGrpcContextComponentSet(const FCF_ComponentSetMessageBase ECSStreamGrpcContextComponentSet);
};
