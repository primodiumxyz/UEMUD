// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/DataAssets/DA_UEM_WorldSettings.h"

void US_UEM_LoadWorldSettings::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());

	const UDA_UEM_WorldSettings* WorldSettings = GetDefault<UDA_UEM_WorldSettings>();
	ComponentMappings = WorldSettings->ComponentMappings.LoadSynchronous();

	const FCF_Context WorldSettingsContext = UCF_Statics::CreateNewContext(this);
	const FC_UEM_WorldSettings WorldSettingsComponent = FC_UEM_WorldSettings(
		WorldSettings->WorldContractAddress,
		WorldSettings->JsonRPCUrl,
		WorldSettings->ChainId,
		ComponentMappings);
	UCF_Statics::SetComponentOfContextId<FC_UEM_WorldSettings>(this,WorldSettingsContext.ContextId,WorldSettingsComponent);
}
