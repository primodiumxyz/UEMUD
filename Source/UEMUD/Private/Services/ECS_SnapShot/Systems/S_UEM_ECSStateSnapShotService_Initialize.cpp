// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/ECS_SnapShot/Systems/S_UEM_ECSStateSnapShotService_Initialize.h"
#include "TurboLinkGrpcConfig.h"
#include "TurboLinkGrpcManager.h"
#include "TurboLinkGrpcUtilities.h"
#include "Core/Context/CF_Context.h"
#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "SEcssnapshot/EcsSnapshotService.h"
#include "Services/ECS_SnapShot/Components/C_UEM_ECSStateSnapshotService.h"
#include "Services/ECS_SnapShot/Messages/M_UEM_OnECSStateSnapshotService_StateChanged.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"

FString US_UEM_ECSStateSnapShotService_Initialize::GetEndPointName()
{
	return "ECSStateSnapshotService";
}

void US_UEM_ECSStateSnapShotService_Initialize::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass()); // world settings should be loaded
	
	FString ECSStreamServiceEndPoint = UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(GetEndPointName());
	

	UTurboLinkGrpcManager* turboLinkManager = UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(this);
	UECSStateSnapshotService* ECSStateSnapshotService = Cast<UECSStateSnapshotService>(turboLinkManager->MakeService(GetEndPointName()));
	if (ECSStateSnapshotService == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find  ECSSnapshotService Service!"));
		return;
	}
	ECSStateSnapshotService->OnServiceStateChanged.AddUniqueDynamic(this, &US_UEM_ECSStateSnapShotService_Initialize::On_ECSStateSnapshotService_StateChanged);
	ECSStateSnapshotService->Connect();


	const FCF_Context ECSStreamServiceContext = UCF_Statics::CreateNewContext(this);
	UCF_Statics::SetComponentOfContextId<FC_UEM_ECSStateSnapshotService>(
		this,
		ECSStreamServiceContext.ContextId,
		FC_UEM_ECSStateSnapshotService(ECSStateSnapshotService));

	UE_LOG(LogTemp, Log, TEXT("ECS Snapshot Initialized"));
}




void US_UEM_ECSStateSnapShotService_Initialize::On_ECSStateSnapshotService_StateChanged(EGrpcServiceState NewState) 
{
	UCF_EventStatics::FireEvent_Template<FM_UEM_OnECSStateSnapshotService_StateChanged>(this,FM_UEM_OnECSStateSnapshotService_StateChanged(NewState));
}

	
