// Fill out your copyright notice in the Description page of Project Settings.


#include "Sync/FL_ST_Sync.h"

#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Sync/Components/MudEntityIdMapping/C_UEM_MudEntityIdMapping.h"

int32 UFL_ST_Sync::GetContextIdForEntityId(UObject* WorldContextObject, FString entityId)
{
	FC_UEM_MudEntityIdMapping MudEntityIdMapping = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_MudEntityIdMapping>(WorldContextObject);
	if(!MudEntityIdMapping.MudEntityIdToLocalContextId.Contains(entityId))
	{
		int32 contextId = UCF_Statics::CreateNewContext(WorldContextObject).ContextId;
		MudEntityIdMapping.MudEntityIdToLocalContextId.Add(entityId,contextId);
		UCF_GroupsStatics::SetSingletonComponent<FC_UEM_MudEntityIdMapping>(WorldContextObject,MudEntityIdMapping);
		return contextId;
	}
	else
	{
		return MudEntityIdMapping.MudEntityIdToLocalContextId[entityId];
	}
}

FString UFL_ST_Sync::GetEntityIdForContextId(UObject* WorldContextObject, int32 contextId)
{
	FC_UEM_MudEntityIdMapping MudEntityIdMapping = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_MudEntityIdMapping>(WorldContextObject);
	for (auto MudEntityIdToLocalContextId : MudEntityIdMapping.MudEntityIdToLocalContextId)
	{
		if(MudEntityIdToLocalContextId.Value == contextId)
			return MudEntityIdToLocalContextId.Key;
	}
	throw;
}

bool UFL_ST_Sync::EntityIdExistsForContextId(UObject* WorldContextObject, int32 contextId)
{
	FC_UEM_MudEntityIdMapping MudEntityIdMapping = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_MudEntityIdMapping>(WorldContextObject);
	for (const auto MudEntityIdToLocalContextId : MudEntityIdMapping.MudEntityIdToLocalContextId)
	{
		if(MudEntityIdToLocalContextId.Value == contextId)
			return true;
	}
	return false;
}
