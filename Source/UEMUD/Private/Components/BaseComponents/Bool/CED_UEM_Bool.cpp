// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseComponents/Bool/CED_UEM_Bool.h"

#include "Components/BaseComponents/Bool/C_UEM_Bool.h"


FInstancedStruct UCED_UEM_Bool::GetInitializedComponentInstancedStruct()
{
	FInstancedStruct UInt256;
	UInt256.InitializeAs<FC_UEM_Bool>();
	return UInt256;
}



FInstancedStruct UCED_UEM_Bool::GetComponentFromEncodedData(const TArray<uint8>& EncodedValues)
{
	const bool Value = EncodedValues[EncodedValues.Num() - 1] > 0;
	
	FInstancedStruct BoolComponentInstancedStruct = GetInitializedComponentInstancedStruct();
	FC_UEM_Bool& BoolComponent = BoolComponentInstancedStruct.GetMutable<FC_UEM_Bool>();
	BoolComponent.Value = Value;
	
	return BoolComponentInstancedStruct;
}
