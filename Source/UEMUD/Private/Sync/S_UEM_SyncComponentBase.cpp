// Fill out your copyright notice in the Description page of Project Settings.


#include "Sync/S_UEM_SyncComponentBase.h"

#include "Contract/Components/CED_UEM_ComponentBase.h"
#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "Encoding/Components/ComponentIdToEncoderDecoder/C_UEM_MudComponentEncoderDecoders.h"
#include "Encoding/Components/SystemIdToEncoderDecoder/C_UEM_MudSystemEncoderDecoders.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Sync/Components/MudEntityIdMapping/C_UEM_MudEntityIdMapping.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"

int32 US_UEM_SyncComponentBase::GetContextIdForEntityId(FString EntityId) const
{

	FC_UEM_MudEntityIdMapping MudEntityIdMapping = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_MudEntityIdMapping>(this);
	if(!MudEntityIdMapping.MudEntityIdToLocalContextId.Contains(EntityId))
	{
		int32 contextId = UCF_Statics::CreateNewContext(this).ContextId;
		MudEntityIdMapping.MudEntityIdToLocalContextId.Add(EntityId,contextId);
		UCF_GroupsStatics::SetSingletonComponent<FC_UEM_MudEntityIdMapping>(this,MudEntityIdMapping);
		return contextId;
	}
	else
	{
		return MudEntityIdMapping.MudEntityIdToLocalContextId[EntityId];
	}
}

void US_UEM_SyncComponentBase::SynComponent(int32 ContextId, FString ComponentId, TArray<uint8> Value) const
{
	const auto worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const TArray<TSubclassOf<UCED_UEM_ComponentBase>> ComponentMappings = worldSettings.ComponentMappings->MappedComponents;

	FC_UEM_MudComponentEncoderDecoders MudComponentEncoderDecoders = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_MudComponentEncoderDecoders>(this);
	FC_UEM_MudSystemEncoderDecoders MudSystemEncoderDecoders = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_MudSystemEncoderDecoders>(this);
	
	if(!MudComponentEncoderDecoders.ComponentIdToEncoderDecoder.Contains(ComponentId))
	{
		if( MudSystemEncoderDecoders.SystemIdToEncoderDecoder.Contains(ComponentId))
		{
			UE_LOG(LogTemp, Log, TEXT("Mud System Stream: %s" ), *MudSystemEncoderDecoders.SystemIdToEncoderDecoder[ComponentId]->Id);
			return;
		}
		UE_LOG(LogTemp, Error, TEXT("Mud Component not setup: %s" ), *ComponentId);
		return;
	}
	UCED_UEM_ComponentBase* MudComponentContractAbi = MudComponentEncoderDecoders.ComponentIdToEncoderDecoder[ComponentId];
	const FInstancedStruct SyncedComponent = MudComponentContractAbi->GetComponentFromEncodedData(Value);
	UCF_Statics::SetComponentInstancedStructOfContextId(this,ContextId,SyncedComponent);
	
}
