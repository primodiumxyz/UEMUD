// Fill out your copyright notice in the Description page of Project Settings.


#include "Encoding/FL_UEM_Encode.h"

#include "Hex/FL_UEM_HexConversions.h"

FString UFL_UEM_Encode::EncodeNumber(int32 number, bool bPrefix)
{
	if(bPrefix)
		return FString::Printf(TEXT("%#034x"),number);
	return FString::Printf(TEXT("%032x"),number);
}

FString UFL_UEM_Encode::EncodeBool(bool bBool, bool bPrefix)
{
	return bBool ? EncodeNumber(1,bPrefix) : EncodeNumber(0,bPrefix);
}

int32 UFL_UEM_Encode::DecodeNumber(const TArray<uint8>& EncodedValues, int32 StartIndex)
{
	TArray<uint8> numberBytes = TArray<uint8>();
	numberBytes.SetNum(32);
	for (int i = 0; i < 32; ++i)
	{
		numberBytes[i] = EncodedValues[i + StartIndex];
	}
	return UFL_UEM_HexConversions::GetNumberFromBytes(numberBytes);
}

bool UFL_UEM_Encode::DecodeBool(const TArray<uint8>& EncodedValues, int32 StartIndex)
{
	TArray<uint8> numberBytes = TArray<uint8>();
	numberBytes.SetNum(32);
	for (int i = 0; i < 32; ++i)
	{
		numberBytes[i] = EncodedValues[i + StartIndex];
	}
	return UFL_UEM_HexConversions::GetNumberFromBytes(numberBytes) > 0;
}


TArray<uint8> UFL_UEM_Encode::DecodeBytes(const TArray<uint8>& EncodedValues, int32 StartIndex)
{
	TArray<uint8> unknownDataBytes = TArray<uint8>();
	unknownDataBytes.SetNum(32);
	for (int i = 0; i < 32; ++i)
	{
		unknownDataBytes[i] = EncodedValues[i + StartIndex];
	}
	int32 UnknownData = UFL_UEM_HexConversions::GetNumberFromBytes(unknownDataBytes);
	
	TArray<uint8> terrainByteArraySizeBytes = TArray<uint8>();
	terrainByteArraySizeBytes.SetNum(32);
	for (int i = 0; i < 32; ++i)
	{
		terrainByteArraySizeBytes[i] = EncodedValues[i + StartIndex + 32 ];
	}
	const int32 byteArraySize = UFL_UEM_HexConversions::GetNumberFromBytes(terrainByteArraySizeBytes);

	TArray<uint8> byteArray = TArray<uint8>();
	byteArray.SetNum(byteArraySize);
	for (int i = 0; i < byteArraySize; ++i)
	{
		byteArray[i] = EncodedValues[i + StartIndex + 64];
	}
	return byteArray;
	
}
