// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Faucet/S_UEM_FaucetServiceHandler.h"
#include "TurboLinkGrpcConfig.h"
#include "TurboLinkGrpcManager.h"
#include "TurboLinkGrpcUtilities.h"
#include "Core/Subsystems/S_CF_Core.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Services/Faucet/Messages/M_UEM_FaucetServiceDripDevResponse.h"
#include "Services/Faucet/Messages/M_UEM_FaucetServiceRequestDripDev.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"

FString US_UEM_FaucetServiceHandler::GetEndPointName()
{
	return "FaucetService";
}

void US_UEM_FaucetServiceHandler::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Super::Initialize(Collection);
	UTurboLinkGrpcManager* turboLinkManager = UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(this);
	FString FaucetServiceEndPoint = UTurboLinkGrpcUtilities::GetTurboLinkGrpcConfig()->GetServiceEndPoint(GetEndPointName());


	FaucetService = Cast<UFaucetService>(turboLinkManager->MakeService(GetEndPointName()));
	if (FaucetService == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find  FaucetService Service!"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Try Connect Faucet"));
	FaucetService->OnServiceStateChanged.AddUniqueDynamic(this, &US_UEM_FaucetServiceHandler::On_FaucetService_StateChanged);
	FaucetService->Connect();

	UCF_EventStatics::AddLambdaListener<FM_UEM_FaucetServiceRequestDripDev>(this,
		[this](const UObject* Invoker,const FM_UEM_FaucetServiceRequestDripDev  FaucetServiceRequestDripDev)
	{
		OnFaucetServiceRequestDripDev(FaucetServiceRequestDripDev);
	});
}


void US_UEM_FaucetServiceHandler::On_FaucetService_StateChanged(EGrpcServiceState NewState)
{
	if(NewState == EGrpcServiceState::Ready)
	{
		UE_LOG(LogTemp, Log, TEXT("Faucet Drip Connected"));
		SubscribeToFaucet();
	}
}


void US_UEM_FaucetServiceHandler::SubscribeToFaucet()
{
	UE_LOG(LogTemp, Log, TEXT("Try Client Connect Faucet"));
	if (FaucetService != nullptr && 
	  FaucetService->GetServiceState() == EGrpcServiceState::Ready &&
	  FaucetServiceClient == nullptr)
	{
		//create client
		FaucetServiceClient = FaucetService->MakeClient();
		

		FaucetServiceClient->OnDripDevResponse.AddUniqueDynamic(this, &US_UEM_FaucetServiceHandler::On_RequestDripDev_Response);
		FaucetGrpcContextHandle = FaucetServiceClient->InitDripDev();
		UE_LOG(LogTemp, Log, TEXT("Client Connect Faucet Success"));


		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, [this]
			{
				UCF_EventStatics::FireEvent_Template<FM_UEM_FaucetServiceRequestDripDev>(this,FM_UEM_FaucetServiceRequestDripDev());
			}
			, 30, true);

		
	}




	
}

void US_UEM_FaucetServiceHandler::RequestDripDev(FString WalletAddress)
{
	UE_LOG(LogTemp, Log, TEXT("Try Faucet Drip: %s"),*WalletAddress);
	FGrpcFaucetDripDevRequest DripDevRequest;
	DripDevRequest.Address = WalletAddress;
	FaucetServiceClient->DripDev(FaucetGrpcContextHandle,DripDevRequest);
}

void US_UEM_FaucetServiceHandler::On_RequestDripDev_Response(FGrpcContextHandle Handle, const FGrpcResult& Result,
	const FGrpcFaucetDripResponse& Response)
{

	UCF_EventStatics::FireEvent_Template<FM_UEM_FaucetServiceDripDevResponse>(this,FM_UEM_FaucetServiceDripDevResponse(Handle,Result,Response));
	if(Result.Code == EGrpcResultCode::Ok)
	{
		UE_LOG(LogTemp, Log, TEXT("Faucet Drip aquired tx hash: %s , ecs hash: %s"),*Response.DripTxHash,*Response.EcsTxHash);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Drip Failed"));
	}
}

void US_UEM_FaucetServiceHandler::OnFaucetServiceRequestDripDev(
	FM_UEM_FaucetServiceRequestDripDev FM_UEM_FaucetServiceRequestDripDev)
{
	
	if(FM_UEM_FaucetServiceRequestDripDev.WalletAddress.Equals("0x"))
	{
		const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);
		FM_UEM_FaucetServiceRequestDripDev.WalletAddress = wallet.EthWalletAddress;
	}
	if (FaucetService != nullptr &&
	  FaucetServiceClient != nullptr)
	{
		RequestDripDev(FM_UEM_FaucetServiceRequestDripDev.WalletAddress);
	}
}
	
