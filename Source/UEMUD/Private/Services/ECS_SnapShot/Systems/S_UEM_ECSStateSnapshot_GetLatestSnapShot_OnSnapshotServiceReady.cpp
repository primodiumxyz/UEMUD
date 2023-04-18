// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/ECS_SnapShot/Systems/S_UEM_ECSStateSnapshot_GetLatestSnapShot_OnSnapshotServiceReady.h"

#include "Core/Component/Messages/ComponentSet/CF_ComponentSetMessage.h"
#include "Services/ECS_SnapShot/Components/C_UEM_ECSStateSnapshotGrpcContext.h"
#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"
#include "EventSystem/Subsystems/S_CF_Event.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "SEcssnapshot/EcsSnapshotService.h"
#include "Services/ECS_SnapShot/Components/C_UEM_ECSStateSnapshotService.h"
#include "Services/ECS_SnapShot/Components/C_UEM_ECSStateSnapshotServiceClient.h"
#include "Services/ECS_SnapShot/Systems/S_UEM_ECSStateSnapShotService_Initialize.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"


void US_UEM_ECSStateSnapshot_GetLatestSnapShot_OnSnapshotServiceReady::Initialize(FSubsystemCollectionBase& Collection)
{

	Super::Initialize(Collection);
	Collection.InitializeDependency(US_UEM_ECSStateSnapShotService_Initialize::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());

	

	UCF_EventStatics::AddLambdaListener<FCF_ComponentSetMessageBase,FC_UEM_ECSStateSnapshotGrpcContext>(this,
		[this](const UObject* Invoker,const FCF_ComponentSetMessageBase ECSServiceGrpcContextComponentSet)
	{
		OnECSStateSnapshotGrpcContextComponentSet(ECSServiceGrpcContextComponentSet);
	});
	
}

void US_UEM_ECSStateSnapshot_GetLatestSnapShot_OnSnapshotServiceReady::OnECSStateSnapshotGrpcContextComponentSet(
	const FCF_ComponentSetMessageBase ECSStateSnapshotGrpcContextComponentSet)
{
	UE_LOG(LogTemp, Log, TEXT("On StateSnapshot Client Ready so Subscribe to ECS StateSnapshot"));
	UECSStateSnapshotService* ECSStateSnapshotService = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ECSStateSnapshotService>
	(this).ECSStateSnapshotService;
	
	UECSStateSnapshotServiceClient* ECSStateSnapshotServiceClient = UCF_GroupsStatics::
	GetSingletonComponent<FC_UEM_ECSStateSnapshotServiceClient>
	(this).ECSStateSnapshotServiceClient;
	
	FGrpcContextHandle ECSStateSnapshotContextHandle = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_ECSStateSnapshotGrpcContext>
	(this).GrpcContextHandle;
	
	FC_UEM_WorldSettings WorldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>
	(this);
	

	FGrpcEcssnapshotECSStateRequestLatestStream snapshotRequest;
	snapshotRequest.ChunkPercentage  = 1;
	snapshotRequest.WorldAddress =WorldSettings.WorldContractAddress; 
	ECSStateSnapshotServiceClient->GetStateLatestStream(ECSStateSnapshotContextHandle,snapshotRequest);
	UE_LOG(LogTemp, Log, TEXT("On Snapshot Client Ready requested latest SnapShot for World: %s"),*snapshotRequest.WorldAddress);
}

void US_UEM_ECSStateSnapshot_GetLatestSnapShot_OnSnapshotServiceReady::GetLatestSnapShot()
{
	OnECSStateSnapshotGrpcContextComponentSet(FCF_ComponentSetMessageBase());
}
