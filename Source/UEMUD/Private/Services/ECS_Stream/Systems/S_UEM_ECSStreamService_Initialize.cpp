// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/ECS_Stream/Systems/S_UEM_ECSStreamService_Initialize.h"

#include "TurboLinkGrpcConfig.h"
#include "TurboLinkGrpcManager.h"
#include "TurboLinkGrpcUtilities.h"
#include "Core/Context/CF_Context.h"
#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "Services/ECS_Stream/Components/C_UEM_ECSStreamService.h"
#include "Services/ECS_Stream/Messages/M_UEM_OnECSStreamService_StateChanged.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"

FString US_UEM_ECSStreamService_Initialize::GetEndPointName()
{
	return "ECSStreamService";
}

void US_UEM_ECSStreamService_Initialize::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass()); // world settings should be loaded
	
	FString ECSStreamServiceEndPoint = UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(GetEndPointName());
	

	UTurboLinkGrpcManager* turboLinkManager = UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(this);
	UECSStreamService* ECSStreamService = Cast<UECSStreamService>(turboLinkManager->MakeService(GetEndPointName()));
	if (ECSStreamService == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find  ECSStreamService Service!"));
		return;
	}
	ECSStreamService->OnServiceStateChanged.AddUniqueDynamic(this, &US_UEM_ECSStreamService_Initialize::On_ECSStreamService_StateChanged);
	ECSStreamService->Connect();


	const FCF_Context ECSStreamServiceContext = UCF_Statics::CreateNewContext(this);
	UCF_Statics::SetComponentOfContextId<FC_UEM_ECSStreamService>(
		this,
		ECSStreamServiceContext.ContextId,
		FC_UEM_ECSStreamService(ECSStreamService));
	UE_LOG(LogTemp, Log, TEXT("ECS Stream Initialized"));
}




void US_UEM_ECSStreamService_Initialize::On_ECSStreamService_StateChanged(EGrpcServiceState NewState) 
{
	UCF_EventStatics::FireEvent_Template<FM_UEM_OnECSStreamService_StateChanged>(this,FM_UEM_OnECSStreamService_StateChanged(NewState));
}

	
