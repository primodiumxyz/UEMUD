// Fill out your copyright notice in the Description page of Project Settings.


#include "Sync/Systems/S_UEM_SyncInitialize.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Sync/Components/MudEntityIdMapping/C_UEM_MudEntityIdMapping.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"

struct FC_UEM_WorldSettings;

void US_UEM_SyncInitialize::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());


	FC_UEM_MudEntityIdMapping MudEntityIdMappingComponent =FC_UEM_MudEntityIdMapping();
	FCF_Context SyncContext = UCF_Statics::CreateNewContext(this);
	UCF_Statics::SetComponentOfContextId<FC_UEM_MudEntityIdMapping>(this,SyncContext.ContextId,MudEntityIdMappingComponent);
	
}
