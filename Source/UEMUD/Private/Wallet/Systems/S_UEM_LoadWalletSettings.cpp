// Fill out your copyright notice in the Description page of Project Settings.


#include "Wallet/Systems/S_UEM_LoadWalletSettings.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Wallet/Components/Wallet/C_UEM_WalletSettings.h"
#include "Wallet/Settings/DS_UEM_Wallet.h"


void US_UEM_LoadWalletSettings::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());

	const UDS_UEM_Wallet* WalletSettings = GetDefault<UDS_UEM_Wallet>();
	
	const FCF_Context WalletSettingsContext = UCF_Statics::CreateNewContext(this);
	const FC_UEM_WalletSettings WalletSettingsComponent = FC_UEM_WalletSettings(WalletSettings->WalletMode,WalletSettings->DefaultWalletName);
	UCF_Statics::SetComponentOfContextId<FC_UEM_WalletSettings>(this,WalletSettingsContext.ContextId,WalletSettingsComponent);
}
