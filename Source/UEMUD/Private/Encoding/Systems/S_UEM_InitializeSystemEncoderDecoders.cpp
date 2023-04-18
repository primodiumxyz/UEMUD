// Fill out your copyright notice in the Description page of Project Settings.


#include "Encoding/Systems/S_UEM_InitializeSystemEncoderDecoders.h"

#include "Keccak256.h"
#include "Keccak256Helper.h"
#include "Core/Subsystems/S_CF_Core.h"
#include "Encoding/Components/SystemIdToEncoderDecoder/C_UEM_MudSystemEncoderDecoders.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"


void US_UEM_InitializeSystemEncoderDecoders::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());
	
	FCF_Context MudSystemEncoderDecoderContext = UCF_Statics::CreateNewContext(this);

	FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const TArray<TSubclassOf<USED_UEM_Base>> SystemMappings = worldSettings.ComponentMappings->MappedSystems;

	TMap<FString,USED_UEM_Base*> SystemIdToEncoderDecoder = TMap<FString,USED_UEM_Base*>();
	for (auto SystemMappingClass : SystemMappings)
	{
		FString MappedComponentId =Cast<USED_UEM_Base>(SystemMappingClass->GetDefaultObject())->Id;
		FString ComponentIdHex = UKeccak256Helper::Keccak256(MappedComponentId);
		USED_UEM_Base* ComponentEncoderDecoder = NewObject<USED_UEM_Base>(this,SystemMappingClass);
		SystemIdToEncoderDecoder.Add(ComponentIdHex,ComponentEncoderDecoder);
	}
	
	FC_UEM_MudSystemEncoderDecoders MudComponentEncoderDecodersComponent = FC_UEM_MudSystemEncoderDecoders(SystemIdToEncoderDecoder);
	UCF_Statics::SetComponentOfContextId<FC_UEM_MudSystemEncoderDecoders>(this,MudSystemEncoderDecoderContext.ContextId,MudComponentEncoderDecodersComponent);
}
