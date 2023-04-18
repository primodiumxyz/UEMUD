// Fill out your copyright notice in the Description page of Project Settings.


#include "Sync/S_UEM_SyncComponentsBasedOnStateSnapshotService.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Services/ECS_SnapShot/Messages/M_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse.h"
#include "Services/ECS_SnapShot/Systems/S_UEM_ECSStateSnapShotService_Initialize.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"


void US_UEM_SyncComponentsBasedOnStateSnapshotService::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_ECSStateSnapShotService_Initialize::StaticClass());
	Collection.InitializeDependency(US_UEM_ECSStateSnapShotService_Initialize::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());

	Super::Initialize(Collection);


	UCF_EventStatics::AddLambdaListener<FM_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse>(this,
	[this](const UObject* Invoker,const FM_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse RequestSubscribeToWorldStream)
	{
		OnECSStateSnapshotServiceResponse(RequestSubscribeToWorldStream);
	});
	UE_LOG(LogTemp, Log, TEXT("Subscribe to ECS Snapshot to Sync Components"));
}


void US_UEM_SyncComponentsBasedOnStateSnapshotService::OnECSStateSnapshotServiceResponse(FM_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse GetStateLatestStreamResponse )
{
	auto worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const TArray<TSubclassOf<UCED_UEM_ComponentBase>> MappedComponents = worldSettings.ComponentMappings->MappedComponents;
	//if(GetStateLatestStreamResponse.Response.State.Num() > 0)
	//	GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Black,"Sync Component Received Snapshot Update");

	auto stateEntityComponents =  GetStateLatestStreamResponse.Response.State;
	auto components = GetStateLatestStreamResponse.Response.StateComponents;
	auto entities = GetStateLatestStreamResponse.Response.StateEntities;

	for (auto entityComponent : stateEntityComponents)
	{
		auto entity = entities[entityComponent.EntityIdIdx];
		auto contextId = GetContextIdForEntityId(entity);
		auto component = components[entityComponent.ComponentIdIdx];
		auto value = entityComponent.Value.Value;
		SynComponent(contextId,component,value);
		
	}
}

