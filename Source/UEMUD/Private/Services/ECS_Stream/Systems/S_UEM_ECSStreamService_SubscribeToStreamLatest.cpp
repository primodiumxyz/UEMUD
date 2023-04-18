// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/ECS_Stream/Systems/S_UEM_ECSStreamService_SubscribeToStreamLatest.h"

#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"
#include "EventSystem/Subsystems/S_CF_Event.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Services/ECS_Stream/Components/C_UEM_ECSStreamServiceGrpcContext.h"
#include "Services/ECS_Stream/Components/C_UEM_ECSStreamService.h"
#include "Services/ECS_Stream/Components/C_UEM_ECSStreamServiceClient.h"
#include "Services/ECS_Stream/Components/C_UEM_ECSStreamServiceGrpcContext.h"
#include "Services/ECS_Stream/Messages/M_UEM_ECSStream_RequestSubscribeToWorldStream.h"
#include "Services/ECS_Stream/Systems/S_UEM_ECSStreamService_Initialize.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"


void US_UEM_ECSStreamService_SubscribeToStreamLatest::Initialize(FSubsystemCollectionBase& Collection)
{

	Super::Initialize(Collection);
	Collection.InitializeDependency(US_UEM_ECSStreamService_Initialize::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());


	UCF_EventStatics::AddLambdaListener<FM_UEM_ECSStream_RequestSubscribeToWorldStream>(this,
		[this](const UObject* Invoker,const FM_UEM_ECSStream_RequestSubscribeToWorldStream RequestSubscribeToWorldStream)
	{
		OnRequestSubscribeToWorldStream(RequestSubscribeToWorldStream);
	});



	UCF_EventStatics::AddLambdaListener<FCF_ComponentSetMessageBase,FC_UEM_ECSStreamServiceGrpcContext>(this,
		[this](const UObject* Invoker,const FCF_ComponentSetMessageBase ECSServiceGrpcContextComponentSet)
	{
		OnECSStreamGrpcContextComponentSet(ECSServiceGrpcContextComponentSet);
	});
	
}

void US_UEM_ECSStreamService_SubscribeToStreamLatest::OnRequestSubscribeToWorldStream(
	FM_UEM_ECSStream_RequestSubscribeToWorldStream RequestSubscribeToWorldStream)
{

	UE_LOG(LogTemp, Log, TEXT("Subscribe to ECS Stream for World: %s"),*RequestSubscribeToWorldStream.EcsstreamECSStreamBlockBundleRequest.WorldAddress);
	
	UECSStreamService* ECSStreamService = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ECSStreamService>(this).ECSStreamService;
	UECSStreamServiceClient* ECSStreamServiceClient = UCF_GroupsStatics::
	GetSingletonComponent<FC_UEM_ECSStreamServiceClient>(this).ECSStreamServiceClient;
	FGrpcContextHandle ECSStreamContextHandle = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ECSStreamServiceGrpcContext>(this).GrpcContextHandle;
	
	if (ECSStreamService != nullptr && 
	  ECSStreamService->GetServiceState() == EGrpcServiceState::Ready &&
	  ECSStreamServiceClient == nullptr)
	{
		ECSStreamServiceClient->SubscribeToStreamLatest(ECSStreamContextHandle,
			RequestSubscribeToWorldStream.EcsstreamECSStreamBlockBundleRequest);
	}

}

void US_UEM_ECSStreamService_SubscribeToStreamLatest::OnECSStreamGrpcContextComponentSet(
	const FCF_ComponentSetMessageBase ECSStreamGrpcContextComponentSet)
{
	UE_LOG(LogTemp, Log, TEXT("On Stream Client Ready so Subscribe to ECS Stream"));
	
	UECSStreamService* ECSStreamService = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ECSStreamService>
	(this).ECSStreamService;
	
	UECSStreamServiceClient* ECSStreamServiceClient = UCF_GroupsStatics::
	GetSingletonComponent<FC_UEM_ECSStreamServiceClient>
	(this).ECSStreamServiceClient;
	
	FGrpcContextHandle ECSStreamContextHandle = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ECSStreamServiceGrpcContext>
	(this).GrpcContextHandle;
	
	FC_UEM_WorldSettings WorldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>
	(this);
	

	FGrpcEcsstreamECSStreamBlockBundleRequest streamRequest;
	streamRequest.WorldAddress = WorldSettings.WorldContractAddress;
	streamRequest.EcsEvents = true;
	streamRequest.BlockHash = true;
	streamRequest.BlockNumber = true;
	streamRequest.BlockTimestamp = true;
	streamRequest.TransactionsConfirmed = true;
	streamRequest.EcsEventsIncludeTxMetadata = true;

		
	ECSStreamServiceClient->SubscribeToStreamLatest(ECSStreamContextHandle,streamRequest);
	UE_LOG(LogTemp, Log, TEXT("On Stream Client Subscribed to ECS Stream for World: %s"), *streamRequest.WorldAddress);
}
