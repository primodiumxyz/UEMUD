// Fill out your copyright notice in the Description page of Project Settings.


#include "Web3Unreal/GetAccounts/Systems/S_UEM_GetAccounts.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Endpoints/GetAccounts.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "Web3Unreal/ChainMetadata/Components/C_UEM_ChainMetadata.h"
#include "Web3Unreal/ChainMetadata/Systems/S_UEM_LoadChainMetadataSettings.h"
#include "Web3Unreal/GetAccounts/Messages/M_UEM_GetAccountsRequest.h"
#include "Web3Unreal/GetAccounts/Messages/M_UEM_GetAccountsResponse.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"


void US_UEM_GetAccounts::Initialize(FSubsystemCollectionBase& Collection)
{


	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadChainMetadataSettings::StaticClass());

	
	UCF_EventStatics::AddLambdaListener<FM_UEM_GetAccountsRequest>(this,
		[this](const UObject* Invoker,const FM_UEM_GetAccountsRequest GetAccountsRequest)
	{
		OnGetAccountsRequest(GetAccountsRequest);
	});
	
}

void US_UEM_GetAccounts::OnGetAccountsRequest(FM_UEM_GetAccountsRequest GetAccountsRequest) const
{
	const FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const FC_UEM_ChainMetadata ChainMetadata= UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ChainMetadata>(this);
	UGetAccounts* GetAccounts = UGetAccounts::GetAccounts(
		this,
		FCString::Atoi(*worldSettings.ChainId),
		ChainMetadata.ChainMetadataJSON);
	GetAccounts->GetOnCompletedDelegate().AddLambda([this](FString Response,int32 StatusCode)
	{
		if(!Response.IsEmpty())
		{
			const FString AccountAddress = Response;
			UCF_EventStatics::FireEvent_Template<FM_UEM_GetAccountsResponse>(this,FM_UEM_GetAccountsResponse(true,StatusCode,Response,AccountAddress));
		}
		else
		{
			UCF_EventStatics::FireEvent_Template<FM_UEM_GetAccountsResponse>(this,FM_UEM_GetAccountsResponse(false,StatusCode,Response,"0x0"));	
		}
	});
	GetAccounts->Activate();
	
}
