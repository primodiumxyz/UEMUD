// Fill out your copyright notice in the Description page of Project Settings.


#include "Encoding/Systems/S_UEM_InitializeComponentEncoderDecoders.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Encoding/Components/ComponentIdToEncoderDecoder/C_UEM_MudComponentEncoderDecoders.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"


void US_UEM_InitializeComponentEncoderDecoders::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());
	
	FCF_Context MudComponentEncoderDecoderContext = UCF_Statics::CreateNewContext(this);

	FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const TArray<TSubclassOf<UCED_UEM_ComponentBase>> ComponentMappings = worldSettings.ComponentMappings->MappedComponents;

	TMap<FString,UCED_UEM_ComponentBase*> ComponentIdToEncoderDecoder = TMap<FString,UCED_UEM_ComponentBase*>();
	for (auto ComponentMappingClass : ComponentMappings)
	{
		FString ComponentIdHex =Cast<UCED_UEM_ComponentBase>(ComponentMappingClass->GetDefaultObject())->GetIdHex();
		UCED_UEM_ComponentBase* ComponentEncoderDecoder = NewObject<UCED_UEM_ComponentBase>(this,ComponentMappingClass);
		ComponentIdToEncoderDecoder.Add(ComponentIdHex,ComponentEncoderDecoder);
	}
	
	FC_UEM_MudComponentEncoderDecoders MudComponentEncoderDecodersComponent =FC_UEM_MudComponentEncoderDecoders(ComponentIdToEncoderDecoder);
	UCF_Statics::SetComponentOfContextId<FC_UEM_MudComponentEncoderDecoders>(this,MudComponentEncoderDecoderContext.ContextId,MudComponentEncoderDecodersComponent);
}
