// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Mode/Systems/S_UEM_ModeService_Initialize.h"
#include "TurboLinkGrpcConfig.h"
#include "TurboLinkGrpcManager.h"
#include "TurboLinkGrpcUtilities.h"
#include "Core/Context/CF_Context.h"
#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "SEcssnapshot/EcsSnapshotService.h"
#include "Services/Mode/Components/C_UEM_ModeService.h"
#include "Services/Mode/Messages/M_UEM_OnModeService_StateChanged.h"
#include "SMode/ModeService.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"


FString US_UEM_ModeService_Initialize::GetEndPointName()
{
	return "QueryLayer";
}

void US_UEM_ModeService_Initialize::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass()); // world settings should be loaded
	
	FString ECSStreamServiceEndPoint = UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(GetEndPointName());
	

	UTurboLinkGrpcManager* turboLinkManager = UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(this);
	UQueryLayer* ModeService = Cast<UQueryLayer>(turboLinkManager->MakeService(GetEndPointName()));
	if (ModeService == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find  Mode Service!"));
		return;
	}
	ModeService->OnServiceStateChanged.AddUniqueDynamic(this, &US_UEM_ModeService_Initialize::On_ModeService_StateChanged);
	ModeService->Connect();


	const FCF_Context ECSStreamServiceContext = UCF_Statics::CreateNewContext(this);
	UCF_Statics::SetComponentOfContextId<FC_UEM_ModeService>(
		this,
		ECSStreamServiceContext.ContextId,
		FC_UEM_ModeService(ModeService));

	UE_LOG(LogTemp, Log, TEXT("Mode Initialized"));
}




void US_UEM_ModeService_Initialize::On_ModeService_StateChanged(EGrpcServiceState NewState) 
{
	UCF_EventStatics::FireEvent_Template<FM_UEM_OnModeService_StateChanged>(this,FM_UEM_OnModeService_StateChanged(NewState));
}

	