// Fill out your copyright notice in the Description page of Project Settings.


#include "Web3Unreal/SendContract/Systems/S_UEM_SendContract.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Endpoints/SendContract.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "Web3Unreal/FL_UEM_Web3EthereumRpcCalls.h"
#include "Web3Unreal/ChainMetadata/Components/C_UEM_ChainMetadata.h"
#include "Web3Unreal/ChainMetadata/Systems/S_UEM_LoadChainMetadataSettings.h"
#include "Web3Unreal/SendContract/Messages/M_UEM_SendContractRequest.h"
#include "Web3Unreal/SendContract/Messages/M_UEM_SendContractResponse.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"


void US_UEM_SendContract::Initialize(FSubsystemCollectionBase& Collection)
{


	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadChainMetadataSettings::StaticClass());

	
	UCF_EventStatics::AddLambdaListener<FM_UEM_SendContractRequest>(this,
		[this](const UObject* Invoker,const FM_UEM_SendContractRequest SendContractRequest)
	{
		OnSendContractRequest(SendContractRequest);
	});
	
}

void US_UEM_SendContract::OnSendContractRequest(FM_UEM_SendContractRequest SendContractRequest) const
{
	const FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);
	const FC_UEM_ChainMetadata ChainMetadata= UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ChainMetadata>(this);
	USendContract* SendContract = USendContract::SendContract(
		this,
		SendContractRequest.ContractAddress,
		SendContractRequest.FunctionName,
		SendContractRequest.ABI,
		SendContractRequest.Params,
		-1,
		"",
		FCString::Atoi(*worldSettings.ChainId),
		ChainMetadata.ChainMetadataJSON);
	SendContract->GetOnCompletedDelegate().AddLambda([this](FString Response,int32 StatusCode)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response);
		if(FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{
			if(JsonObject->HasField("result"))
			{
				const FString TransactionHash = JsonObject->GetStringField("result");
				UCF_EventStatics::FireEvent_Template<FM_UEM_SendContractResponse>(this,FM_UEM_SendContractResponse(true,StatusCode,Response,TransactionHash));
			}
			else
			{
				UE_LOG(LogTemp,Error,
				TEXT("No field 'result' in response: %s"),
				*Response);
			}
		}
		UCF_EventStatics::FireEvent_Template<FM_UEM_SendContractResponse>(this,FM_UEM_SendContractResponse(false,StatusCode,Response,"0x0"));
	});
	SendContract->Activate();
	
}
