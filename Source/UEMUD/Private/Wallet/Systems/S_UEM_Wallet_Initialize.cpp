// Fill out your copyright notice in the Description page of Project Settings.


#include "Wallet/Systems/S_UEM_Wallet_Initialize.h"

#include "Secp256k1Helper.h"
#include "Core/Subsystems/S_CF_Core.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Wallet/Wallet_Library.h"
#include "Wallet/Components/Wallet/C_UEM_LocalWallet.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "Wallet/Components/Wallet/C_UEM_WalletSettings.h"
#include "Wallet/Systems/S_UEM_LoadWalletSettings.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"

void US_UEM_Wallet_Initialize::Initialize(FSubsystemCollectionBase& Collection)
{


	Super::Initialize(Collection);
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWalletSettings::StaticClass());

	const FC_UEM_WalletSettings WalletSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletSettings>(this);

	
	TArray<uint8> WalletPrivateKey;
	
	if(UWallet_Library::WalletExists(WalletSettings.DefaultWalletName))
	{
		WalletPrivateKey = UWallet_Library::ReadWallet(WalletSettings.DefaultWalletName);
	}
	else
	{
		WalletPrivateKey = UWallet_Library::CreateWallet(WalletSettings.DefaultWalletName);
	}
	
	
	const FCF_Context LocalWalletContext = UCF_Statics::CreateNewContext(this);
	const FC_UEM_LocalWallet LocalWallet =FC_UEM_LocalWallet(WalletPrivateKey);
	UCF_Statics::SetComponentOfContextId<FC_UEM_LocalWallet>(this,LocalWalletContext.ContextId,LocalWallet);

	if(WalletSettings.WalletMode == EWalletMode::Local)
	{
		const FString EthWalletAddress = USecp256k1Helper::CalcPublicAddressFromPrivateKey(WalletPrivateKey.GetData());
		if(UCF_GroupsStatics::DoesSingletonComponentExist<FC_UEM_WalletAddress>(this))
		{
			UCF_GroupsStatics::SetSingletonComponent<FC_UEM_WalletAddress>(this,FC_UEM_WalletAddress(EthWalletAddress));	
		}
		else
		{
			const FCF_Context MapVisualContext = UCF_Statics::CreateNewContext(this);
			UCF_Statics::SetComponentOfContextId<FC_UEM_WalletAddress>(this,MapVisualContext.ContextId,FC_UEM_WalletAddress(EthWalletAddress));
		}
	}
	
	
}
