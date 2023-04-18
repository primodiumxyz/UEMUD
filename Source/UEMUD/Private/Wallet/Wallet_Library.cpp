// Fill out your copyright notice in the Description page of Project Settings.


#include "Wallet/Wallet_Library.h"

#include "Secp256k1Helper.h"
#include "Web3Utils.h"
#include "Kismet/GameplayStatics.h"


TArray<uint8> UWallet_Library::CreateWallet(FString WalletName)
{
	UWalletSave* walletSave = Cast<UWalletSave>(UGameplayStatics::CreateSaveGameObject(UWalletSave::StaticClass()));
	const FAccount Account = USecp256k1Helper::GenerateNewAccount();
	walletSave->WalletPrivateKey = UWeb3Utils::GetPrivateKeyBytes(Account.privateKey);
	UGameplayStatics::SaveGameToSlot(walletSave,WalletName,0);
	return walletSave->WalletPrivateKey;
}

bool UWallet_Library::WalletExists(FString WalletName)
{
	return UGameplayStatics::DoesSaveGameExist(WalletName,0);
}

UWalletSave* UWallet_Library::GetWallet(FString WalletName)
{
	return Cast<UWalletSave>(UGameplayStatics::LoadGameFromSlot(WalletName,0));
}

TArray<uint8> UWallet_Library::ReadWallet(FString WalletName)
{
	if(WalletExists(WalletName))
		return GetWallet(WalletName)->WalletPrivateKey;
	else
		return CreateWallet(WalletName);
}

void UWallet_Library::SaveWalletAs(TArray<uint8> PrivateKey, FString WalletName)
{
	UWalletSave* walletSave = Cast<UWalletSave>(UGameplayStatics::CreateSaveGameObject(UWalletSave::StaticClass()));
	walletSave->WalletPrivateKey = PrivateKey;
	UGameplayStatics::SaveGameToSlot(walletSave,WalletName,0);
}
