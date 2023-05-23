// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Mode/Systems/S_UEM_ModeService_ConnectClient.h"

#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "Keccak256Helper.h"
#include "Web3Utils.h"
#include "Contract/Tables/C_UEM_TableDefinitions.h"
#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"
#include "EventSystem/Subsystems/S_CF_Event.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Services/Mode/Components/C_UEM_Mode_GetStateGrpcContext.h"
#include "Services/Mode/Components/C_UEM_ModeService.h"
#include "Services/Mode/Components/C_UEM_ModeServiceClient.h"
#include "Services/Mode/Components/C_UEM_Mode_GetStreamStateGrpcContext.h"
#include "Services/Mode/Messages/M_UEM_OnModeService_StateChanged.h"
#include "Services/Mode/Systems/S_UEM_ModeService_Initialize.h"
#include "Services/Mode/Messages/M_UEM_OnModeService_StateChanged.h"
#include "Services/Mode/Messages/M_UEM_OnModeService_StreamStateResponse.h"
#include "Sync/Components/MudEntityIdMapping/C_UEM_MudEntityIdMapping.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"


void US_UEM_ModeService_ConnectClient::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(US_UEM_ModeService_Initialize::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());


	UCF_EventStatics::AddLambdaListener<FM_UEM_OnModeService_StateChanged>
	(this,[this]
		(const UObject* Invoker,
			const FM_UEM_OnModeService_StateChanged ModeServiceStateChanged)
	{
		OnModeServiceStateChanged(ModeServiceStateChanged);
	});
	
	
}

void US_UEM_ModeService_ConnectClient::OnModeServiceStateChanged(FM_UEM_OnModeService_StateChanged ModeServiceStateChanged)
{
	EGrpcServiceState ReceivedState = ModeServiceStateChanged.NewState;
	UE_LOG(LogTemp, Log, TEXT("Try Mode Client Connect Received State: %s"),*(UEnum::GetValueAsString(ReceivedState)));
	UQueryLayer* ModeService = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ModeService>(this).QueryLayerService;

	const int32 ECSServiceContextId =UCF_GroupsStatics::GetSingletonComponentContextId<FC_UEM_ModeService>(this);
	
	EGrpcServiceState State = ModeService->GetServiceState();
	if (ModeService != nullptr && 
	  State == EGrpcServiceState::Ready &&
	  !UCF_GroupsStatics::DoesSingletonComponentExist<FC_UEM_ModeServiceClient>(this))
	{
		
		UQueryLayerClient* ModeServiceClient = ModeService->MakeClient();
		
		UCF_Statics::SetComponentOfContextId<FC_UEM_ModeServiceClient>(
			this,
			ECSServiceContextId,
			FC_UEM_ModeServiceClient(ModeServiceClient));

		

		ModeServiceClient->OnStreamStateResponse.AddUniqueDynamic(this, &US_UEM_ModeService_ConnectClient::OnModeService_GetStreamStateResponse);
		ModeServiceClient->OnGetStateResponse.AddUniqueDynamic(this, &US_UEM_ModeService_ConnectClient::OnModeService_GetStateResponse );

		if (ModeService == nullptr ||
		(ModeService->GetServiceState() != EGrpcServiceState::Ready && ModeService->GetServiceState() != EGrpcServiceState::Idle) ||
		ModeService == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Connect to Mode service first!"));
			return;
		}

		const FGrpcContextHandle Mode_GetStateGrpcGrpcContextHandle = ModeServiceClient->InitGetState();
		UCF_Statics::SetComponentOfContextId<FC_UEM_Mode_GetStateGrpcContext>(
			this,
			ECSServiceContextId,
			FC_UEM_Mode_GetStateGrpcContext(Mode_GetStateGrpcGrpcContextHandle));


		const FGrpcContextHandle Mode_GetStreamStateGrpcGrpcContextHandle = ModeServiceClient->InitStreamState();
		UCF_Statics::SetComponentOfContextId<FC_UEM_Mode_GetStreamStateGrpcContext>(
			this,
			ECSServiceContextId,
			FC_UEM_Mode_GetStreamStateGrpcContext(Mode_GetStreamStateGrpcGrpcContextHandle));

		UE_LOG(LogTemp, Log, TEXT("Mode Client Connected"));

		
		FC_UEM_WorldSettings WorldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>
			(this);

		
		FGrpcModeStateRequest ModeStateRequest;
		ModeStateRequest.Namespace.ChainId = WorldSettings.ChainId;
		ModeStateRequest.Namespace.WorldAddress =WorldSettings.WorldContractAddress;
		
		ModeServiceClient->GetState(Mode_GetStateGrpcGrpcContextHandle,ModeStateRequest);
		
		
	}
		
}

void US_UEM_ModeService_ConnectClient::OnModeService_GetStateResponse(FGrpcContextHandle Handle,
	const FGrpcResult& Result, const FGrpcModeQueryLayerStateResponse& Response)
{
	UE_LOG(LogTemp, Log, TEXT("Mode Client Received State Response"));

	
	
	OnModeQueryLayerStateResponse(Response,ESyncType::Set);
	
	const FC_UEM_ModeServiceClient ModeServiceClientComponent =  UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ModeServiceClient>(this);
	const FC_UEM_Mode_GetStreamStateGrpcContext GetStreamStateGrpcContextComponent =  UCF_GroupsStatics::GetSingletonComponent<FC_UEM_Mode_GetStreamStateGrpcContext>(this);
	FC_UEM_WorldSettings WorldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>
			(this);

		
	FGrpcModeStateRequest ModeStateRequest;
	ModeStateRequest.Namespace.ChainId = WorldSettings.ChainId;
	ModeStateRequest.Namespace.WorldAddress =WorldSettings.WorldContractAddress;
	
	ModeServiceClientComponent.QueryLayerServiceClient->StreamState(GetStreamStateGrpcContextComponent.GrpcContextHandle,ModeStateRequest);
}

void US_UEM_ModeService_ConnectClient::OnModeService_GetStreamStateResponse(FGrpcContextHandle Handle,
                                                             const FGrpcResult& Result, const FGrpcModeQueryLayerStateStreamResponse& Response)
{
	if(Response.Deleted.ChainTables.Num() <= 0 &&
		Response.Deleted.WorldTables.Num() <= 0 &&
		Response.Inserted.WorldTables.Num() <= 0 &&
		Response.Updated.WorldTables.Num() <= 0)
			return;
			
	OnModeQueryLayerStateResponse(Response.Inserted,ESyncType::Set);
	OnModeQueryLayerStateResponse(Response.Updated,ESyncType::Update);
	OnModeQueryLayerStateResponse(Response.Deleted,ESyncType::Delete);
	
	UE_LOG(LogTemp, Log, TEXT("Mode Client Received Stream State Response"));
	//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Green,"ECS StateSnapshot Client Received StateSnapshot Update"  );
	UCF_EventStatics::FireEvent_Template<FM_UEM_OnModeService_StreamStateResponse>(this,
	FM_UEM_OnModeService_StreamStateResponse(Handle,Result,Response));
}



int32 US_UEM_ModeService_ConnectClient::GetContextIdForEntityId(FString EntityId) const
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

void US_UEM_ModeService_ConnectClient::OnModeQueryLayerStateResponse(
	FGrpcModeQueryLayerStateResponse QueryLayerStateResponse, ESyncType SyncType)
{
	const FC_UEM_TableDefinitions TableDefinitionsComponent = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_TableDefinitions>(this);
	
	for (auto WorldTable : QueryLayerStateResponse.WorldTables)
	{
		if(TableDefinitionsComponent.TableDefinitions.Contains(WorldTable.Key))
		{
			//first one is id
			for (int i = 0; i < WorldTable.Value.Rows.Num(); ++i)
			{
				FString EntityId = "";
				for (int charIndex = 0; charIndex < WorldTable.Value.Rows[i].Values[0].Value.Num(); ++charIndex)
				{
					EntityId.AppendChar(WorldTable.Value.Rows[i].Values[0].Value[charIndex]);
				}
				int32 ContextId = GetContextIdForEntityId(EntityId);
				

				
				FString TableComponentJson = "{";
				for (int j = 1; j < WorldTable.Value.Rows[i].Values.Num(); ++j)
				{
					const FString MemberName = WorldTable.Value.Cols[j];
					//FString Value = BytesToString(WorldTable.Value.Rows[i].Values[j].Value.GetData(),WorldTable.Value.Rows[i].Values[j].Value.Num());
					FString Value = "";
					if(
						WorldTable.Value.Types[j].Equals("uint") ||
						WorldTable.Value.Types[j].Equals("uint8") ||
						WorldTable.Value.Types[j].Equals("uint16") ||
						WorldTable.Value.Types[j].Equals("uint32") ||
						WorldTable.Value.Types[j].Equals("int") ||
						WorldTable.Value.Types[j].Equals("int8") ||
						WorldTable.Value.Types[j].Equals("int16") ||
						WorldTable.Value.Types[j].Equals("int32") ||
						WorldTable.Value.Types[j].Equals("bool") ||
						WorldTable.Value.Types[j].Equals("bytes32")
						)
					{
						for (int charIndex = 0; charIndex < WorldTable.Value.Rows[i].Values[j].Value.Num(); ++charIndex)
						{
							Value.AppendChar(WorldTable.Value.Rows[i].Values[j].Value[charIndex]);
						}	
					}
					else if(WorldTable.Value.Types[j].Equals("string"))
					{
						for (int charIndex = 0; charIndex < WorldTable.Value.Rows[i].Values[j].Value.Num(); ++charIndex)
						{
							Value.AppendChar(WorldTable.Value.Rows[i].Values[j].Value[charIndex]);
						}	
					}
					else if(WorldTable.Value.Types[j].Equals("bytes"))
					{
						Value.AppendChar('[');
						TArray<uint8> ByteArray = TArray<uint8>();
						uint8 currValue = 0;
						for (int charIndex = 3; charIndex < WorldTable.Value.Rows[i].Values[j].Value.Num() - 1; ++charIndex)
						{
							FString SingleByteString;
							SingleByteString.AppendChar(WorldTable.Value.Rows[i].Values[j].Value[charIndex]);
							if(charIndex % 2 == 1)
							{
								currValue = FCString::Atoi(*SingleByteString) * 16;
							}
							else
								currValue += FCString::Atoi(*SingleByteString);
							Value.Append(FString::FromInt(currValue));
							if(charIndex % 2 == 0 && charIndex < WorldTable.Value.Rows[i].Values[j].Value.Num() - 1)
								Value.AppendChar(',');
						}
						Value.AppendChar(']');
					}
					 //= WorldTable.Value.Rows[i].Values[j].Value.ToString()
					
					TableComponentJson.Append(FString::Printf(TEXT("\"%s\""),*MemberName)).Append(":").Append(Value);
					if(j+1 < WorldTable.Value.Rows[i].Values.Num())
						TableComponentJson.Append(",");
				}
				TableComponentJson.Append("}");
				TSharedPtr<FJsonObject> JsonObjectPtr;
				FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(TableComponentJson),JsonObjectPtr);
				FInstancedStruct OutInstancedStruct;
				OutInstancedStruct.InitializeAs(TableDefinitionsComponent.TableDefinitions[WorldTable.Key]);
				
				FJsonObjectConverter::JsonObjectToUStruct(JsonObjectPtr.ToSharedRef(),TableDefinitionsComponent.TableDefinitions[WorldTable.Key],OutInstancedStruct.GetMutableMemory());

				if(SyncType == ESyncType::Delete)
					UCF_Statics::RemoveComponentFromContextId(this,ContextId,OutInstancedStruct);
				else 
					UCF_Statics::SetComponentInstancedStructOfContextId(this,ContextId,OutInstancedStruct);
			}
			
			
		}
	}
}
