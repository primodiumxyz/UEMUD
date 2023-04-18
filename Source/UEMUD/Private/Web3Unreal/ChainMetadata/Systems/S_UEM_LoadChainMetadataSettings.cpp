// Fill out your copyright notice in the Description page of Project Settings.


#include "Web3Unreal/ChainMetadata/Systems/S_UEM_LoadChainMetadataSettings.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Web3Unreal/ChainMetadata/Components/C_UEM_ChainMetadata.h"
#include "Web3Unreal/ChainMetadata/Settings/DS_UEM_ChainMetadata.h"

void US_UEM_LoadChainMetadataSettings::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());

	const UDS_UEM_ChainMetadata* ChainMetadataSettings = GetDefault<UDS_UEM_ChainMetadata>();
	
	const FCF_Context ChainMetadataSettingsContext = UCF_Statics::CreateNewContext(this);
	const FC_UEM_ChainMetadata ChainMetadataSettingsComponent
	= FC_UEM_ChainMetadata(
		ChainMetadataSettings->ChainId,
		ChainMetadataSettings->ChainName,
		ChainMetadataSettings->NativeCurrencyName,
		ChainMetadataSettings->NativeCurrencySymbol,
		ChainMetadataSettings->NativeCurrencyDigits,
		ChainMetadataSettings->RpcUrls);
	UCF_Statics::SetComponentOfContextId<FC_UEM_ChainMetadata>(this,ChainMetadataSettingsContext.ContextId,ChainMetadataSettingsComponent);
}
