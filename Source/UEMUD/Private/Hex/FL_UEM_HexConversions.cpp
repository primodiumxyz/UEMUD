// Fill out your copyright notice in the Description page of Project Settings.


#include "Hex/FL_UEM_HexConversions.h"

#include "Web3Utils.h"

int32 UFL_UEM_HexConversions::GetNumberFromHexString(FString HexString)
{
	return FParse::HexNumber64(*HexString);
}

int32 UFL_UEM_HexConversions::GetNumberFromBytes(const TArray<uint8>& Bytes)
{
	return GetNumberFromHexString(UWeb3Utils::ByteArrayToFString(Bytes));
}
