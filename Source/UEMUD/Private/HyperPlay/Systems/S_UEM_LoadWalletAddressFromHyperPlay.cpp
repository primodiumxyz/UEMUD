// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperPlay/Systems/S_UEM_LoadWalletAddressFromHyperPlay.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "Wallet/Components/Wallet/C_UEM_WalletSettings.h"
#include "Wallet/Systems/S_UEM_Wallet_Initialize.h"
#include "Web3Unreal/GetAccounts/Messages/M_UEM_GetAccountsRequest.h"
#include "Web3Unreal/GetAccounts/Messages/M_UEM_GetAccountsResponse.h"
#include "Web3Unreal/GetAccounts/Systems/S_UEM_GetAccounts.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"

void US_UEM_LoadWalletAddressFromHyperPlay::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());
	Collection.InitializeDependency(US_UEM_Wallet_Initialize::StaticClass());
	Collection.InitializeDependency(US_UEM_GetAccounts::StaticClass());

	
	UCF_EventStatics::AddLambdaListener<FM_UEM_GetAccountsResponse>(this,
		[this](const UObject* Invoker,const FM_UEM_GetAccountsResponse GetAccountsResponse)
	{
		OnGetAccountsResponse(GetAccountsResponse);
	});

	const FC_UEM_WalletSettings WalletSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletSettings>(this);

	if(WalletSettings.WalletMode == EWalletMode::HyperPlay)
	{
		UCF_EventStatics::FireEvent_Template<FM_UEM_GetAccountsRequest>(this,FM_UEM_GetAccountsRequest());
	}
}

void US_UEM_LoadWalletAddressFromHyperPlay::OnGetAccountsResponse(FM_UEM_GetAccountsResponse GetBalanceResponse) const
{
	if(GetBalanceResponse.bSuccess && GetBalanceResponse.AccountAddress != "")
	{
		const FC_UEM_WalletAddress Wallet =FC_UEM_WalletAddress(GetBalanceResponse.AccountAddress);
		if(UCF_GroupsStatics::DoesSingletonComponentExist<FC_UEM_WalletAddress>(this))
				UCF_GroupsStatics::SetSingletonComponent<FC_UEM_WalletAddress>(this,Wallet);
		else
		{
			const FCF_Context WalletAddressContext = UCF_Statics::CreateNewContext(this);
			UCF_Statics::SetComponentOfContextId<FC_UEM_WalletAddress>(this,WalletAddressContext.ContextId,Wallet);
		}
	}
	
	
}
