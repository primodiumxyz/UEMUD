// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/ECS_SnapShot/Systems/S_UEM_ECSStateSnapshotService_ConnectClient.h"
#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"
#include "EventSystem/Subsystems/S_CF_Event.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Services/ECS_SnapShot/Components/C_UEM_ECSStateSnapshotGrpcContext.h"
#include "Services/ECS_SnapShot/Components/C_UEM_ECSStateSnapshotService.h"
#include "Services/ECS_SnapShot/Components/C_UEM_ECSStateSnapshotServiceClient.h"
#include "Services/ECS_SnapShot/Messages/M_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse.h"
#include "Services/ECS_SnapShot/Messages/M_UEM_OnECSStateSnapshotService_StateChanged.h"
#include "Services/ECS_SnapShot/Systems/S_UEM_ECSStateSnapShotService_Initialize.h"


void US_UEM_ECSStateSnapshotService_ConnectClient::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(US_UEM_ECSStateSnapShotService_Initialize::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());


	UCF_EventStatics::AddLambdaListener<FM_UEM_OnECSStateSnapshotService_StateChanged>
	(this,[this]
		(const UObject* Invoker,
			const FM_UEM_OnECSStateSnapshotService_StateChanged ECSStateSnapshotServiceStateChanged)
	{
		OnECSStateSnapshotServiceStateChanged(ECSStateSnapshotServiceStateChanged);
	});
	
	
}

void US_UEM_ECSStateSnapshotService_ConnectClient::OnECSStateSnapshotServiceStateChanged(FM_UEM_OnECSStateSnapshotService_StateChanged ECSStateSnapshotServiceStateChanged)
{
	EGrpcServiceState ReceivedState = ECSStateSnapshotServiceStateChanged.NewState;
	UE_LOG(LogTemp, Log, TEXT("Try ECS Snapshot Client Connect Received State: %s"),*(UEnum::GetValueAsString(ReceivedState)));
	UECSStateSnapshotService* ECSStateSnapshotService = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ECSStateSnapshotService>(this).ECSStateSnapshotService;

	const int32 ECSServiceContextId =UCF_GroupsStatics::GetSingletonComponentContextId<FC_UEM_ECSStateSnapshotService>(this);
	
	EGrpcServiceState State = ECSStateSnapshotService->GetServiceState();
	if (ECSStateSnapshotService != nullptr && 
	  State == EGrpcServiceState::Ready &&
	  !UCF_GroupsStatics::DoesSingletonComponentExist<FC_UEM_ECSStateSnapshotServiceClient>(this))
	{
		
		UECSStateSnapshotServiceClient* ECSStateSnapshotServiceClient = ECSStateSnapshotService->MakeClient();
		
		UCF_Statics::SetComponentOfContextId<FC_UEM_ECSStateSnapshotServiceClient>(
			this,
			ECSServiceContextId,
			FC_UEM_ECSStateSnapshotServiceClient(ECSStateSnapshotServiceClient));

		

		ECSStateSnapshotServiceClient->OnGetStateLatestStreamResponse.AddUniqueDynamic(this, &US_UEM_ECSStateSnapshotService_ConnectClient::OnECSStateSnapshotServiceResponse);


		if (ECSStateSnapshotService == nullptr ||
		(ECSStateSnapshotService->GetServiceState() != EGrpcServiceState::Ready && ECSStateSnapshotService->GetServiceState() != EGrpcServiceState::Idle) ||
		ECSStateSnapshotService == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Connect to StateSnapshot service first!"));
			return;
		}

		const FGrpcContextHandle ECSStateSnapshotServiceContextHandle = ECSStateSnapshotServiceClient->InitGetStateLatestStream();
		UCF_Statics::SetComponentOfContextId<FC_UEM_ECSStateSnapshotGrpcContext>(
			this,
			ECSServiceContextId,
			FC_UEM_ECSStateSnapshotGrpcContext(ECSStateSnapshotServiceContextHandle));

		UE_LOG(LogTemp, Log, TEXT("ECS StateSnapshot Client Connected"));
		

	}
		
}

void US_UEM_ECSStateSnapshotService_ConnectClient::OnECSStateSnapshotServiceResponse(FGrpcContextHandle Handle,
	const FGrpcResult& Result, const FGrpcEcssnapshotECSStateReply& Response)
{
	//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Green,"ECS StateSnapshot Client Received StateSnapshot Update"  );
	UCF_EventStatics::FireEvent_Template<FM_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse>(this,
	FM_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse(Handle,Result,Response));
}
