// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseComponents/UInt32/CED_UEM_UInt32.h"

#include "Components/BaseComponents/UInt32/C_UEM_UInt32.h"
#include "Hex/FL_UEM_HexConversions.h"
#include "Misc/DefaultValueHelper.h"


FInstancedStruct UCED_UEM_UInt32::GetInitializedComponentInstancedStruct()
{
	FInstancedStruct UInt256;
	UInt256.InitializeAs<FC_UEM_UInt32>();
	return UInt256;
}


FInstancedStruct UCED_UEM_UInt32::GetComponentFromEncodedData(const TArray<uint8>& EncodedValues)
{
	const int32 Value = UFL_UEM_HexConversions::GetNumberFromBytes(EncodedValues);
	FInstancedStruct UInt32ComponentInstancedStruct = GetInitializedComponentInstancedStruct();
	FC_UEM_UInt32& UInt32Component = UInt32ComponentInstancedStruct.GetMutable<FC_UEM_UInt32>();
	UInt32Component.Value = Value;
	
	return UInt32ComponentInstancedStruct;
}
