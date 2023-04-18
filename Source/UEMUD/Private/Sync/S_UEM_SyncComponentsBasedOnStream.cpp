// Fill out your copyright notice in the Description page of Project Settings.

#include "Sync/S_UEM_SyncComponentsBasedOnStream.h"
#include "Core/Subsystems/S_CF_Core.h"
#include "EventSystem/Subsystems/S_CF_Event.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Services/ECS_Stream/Messages/M_UEM_OnECSStreamService_SubscribeToStreamLatestResponse.h"
#include "Services/ECS_Stream/Systems/S_UEM_ECSStreamService_Initialize.h"
#include "Services/ECS_Stream/Systems/S_UEM_ECSStreamService_SubscribeToStreamLatest.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"

void US_UEM_SyncComponentsBasedOnStream::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_ECSStreamService_Initialize::StaticClass());
	Collection.InitializeDependency(US_UEM_ECSStreamService_SubscribeToStreamLatest::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());

	Super::Initialize(Collection);


	UCF_EventStatics::AddLambdaListener<FM_UEM_OnECSStreamService_SubscribeToStreamLatestResponse>(this,
	[this](const UObject* Invoker,const FM_UEM_OnECSStreamService_SubscribeToStreamLatestResponse RequestSubscribeToWorldStream)
	{
		OnECSStreamServiceResponse(RequestSubscribeToWorldStream);
	});
	UE_LOG(LogTemp, Log, TEXT("Subscribe to ECS Stream to Sync Components"));
}

bool US_UEM_SyncComponentsBasedOnStream::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}


void US_UEM_SyncComponentsBasedOnStream::OnECSStreamServiceResponse(FM_UEM_OnECSStreamService_SubscribeToStreamLatestResponse ECSServiceSubscribeToStreamLatestResponse )
{
	
	
	auto events = ECSServiceSubscribeToStreamLatestResponse.Response.EcsEvents;
	for (auto ECSEvent : events)
	{
		auto entityId = ECSEvent.EntityId;
		int32 contextId = GetContextIdForEntityId(entityId);
		auto componentId = ECSEvent.ComponentId;
		auto value = ECSEvent.Value.Value;
		SynComponent(contextId,componentId,value);
		UE_LOG(LogTemp, Log, TEXT("Mud Component Synced: %s"),*ECSEvent.ComponentId);
	}
}
