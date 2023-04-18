// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/ECS_Stream/Systems/S_UEM_ECSStreamService_ConnectClient.h"
#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"
#include "EventSystem/Subsystems/S_CF_Event.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Services/ECS_Stream/Components/C_UEM_ECSStreamServiceGrpcContext.h"
#include "Services/ECS_Stream/Components/C_UEM_ECSStreamService.h"
#include "Services/ECS_Stream/Components/C_UEM_ECSStreamServiceClient.h"
#include "Services/ECS_Stream/Messages/M_UEM_OnECSStreamService_SubscribeToStreamLatestResponse.h"
#include "Services/ECS_Stream/Systems/S_UEM_ECSStreamService_Initialize.h"

void US_UEM_ECSStreamService_ConnectClient::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(US_UEM_ECSStreamService_Initialize::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());


	UCF_EventStatics::AddLambdaListener<FM_UEM_OnECSStreamService_StateChanged>(this,[this](const UObject* Invoker,const FM_UEM_OnECSStreamService_StateChanged ECSServiceStateChanged)
	{
		OnECSServiceStateChanged(ECSServiceStateChanged);
	});
	
	
}

void US_UEM_ECSStreamService_ConnectClient::OnECSServiceStateChanged(FM_UEM_OnECSStreamService_StateChanged StateChanged)
{
	UE_LOG(LogTemp, Log, TEXT("Try ECS Stream Client Connect"));
	
	UECSStreamService* ECSStreamService = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ECSStreamService>(this).ECSStreamService;

	const int32 ECSServiceContextId =UCF_GroupsStatics::GetSingletonComponentContextId<FC_UEM_ECSStreamService>(this);
	
	if (ECSStreamService != nullptr && 
	  ECSStreamService->GetServiceState() == EGrpcServiceState::Ready &&
	  !UCF_GroupsStatics::DoesSingletonComponentExist<FC_UEM_ECSStreamServiceClient>(this))
	{
		
		UECSStreamServiceClient* ECSStreamServiceClient = ECSStreamService->MakeClient();
		
		UCF_Statics::SetComponentOfContextId<FC_UEM_ECSStreamServiceClient>(
			this,
			ECSServiceContextId,
			FC_UEM_ECSStreamServiceClient(ECSStreamServiceClient));

		

		ECSStreamServiceClient->OnSubscribeToStreamLatestResponse.AddUniqueDynamic(this, &US_UEM_ECSStreamService_ConnectClient::OnECSStreamServiceResponse);


		if (ECSStreamService == nullptr ||
		(ECSStreamService->GetServiceState() != EGrpcServiceState::Ready && ECSStreamService->GetServiceState() != EGrpcServiceState::Idle) ||
		ECSStreamService == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Connect to stream service first!"));
			return;
		}

		const FGrpcContextHandle ECSStreamServiceContextHandle = ECSStreamServiceClient->InitSubscribeToStreamLatest();
		UCF_Statics::SetComponentOfContextId<FC_UEM_ECSStreamServiceGrpcContext>(
			this,
			ECSServiceContextId,
			FC_UEM_ECSStreamServiceGrpcContext(ECSStreamServiceContextHandle));

		UE_LOG(LogTemp, Log, TEXT("ECS Stream Client Connected"));
		

	}
		
}

void US_UEM_ECSStreamService_ConnectClient::OnECSStreamServiceResponse(FGrpcContextHandle Handle,
	const FGrpcResult& Result, const FGrpcEcsstreamECSStreamBlockBundleReply& Response)
{
	//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Black,"ECS Stream Client Received Stream Update"  );
	UCF_EventStatics::FireEvent_Template<FM_UEM_OnECSStreamService_SubscribeToStreamLatestResponse>(this,
		FM_UEM_OnECSStreamService_SubscribeToStreamLatestResponse(Handle,Result,Response));
}
