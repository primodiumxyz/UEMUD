// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseComponents/Bool/CED_UEM_Bool.h"

#include "Components/BaseComponents/Bool/C_UEM_Bool.h"
#include "Encoding/FL_UEM_Encode.h"


FInstancedStruct UCED_UEM_Bool::GetInitializedComponentInstancedStruct()
{
	FInstancedStruct UInt256;
	UInt256.InitializeAs<FC_UEM_Bool>();
	return UInt256;
}



FInstancedStruct UCED_UEM_Bool::GetComponentFromEncodedData(const TArray<uint8>& EncodedValues)
{
	FInstancedStruct BoolComponentInstancedStruct = GetInitializedComponentInstancedStruct();
	FC_UEM_Bool& BoolComponent = BoolComponentInstancedStruct.GetMutable<FC_UEM_Bool>();
	BoolComponent.Value = UFL_UEM_Encode::DecodeBool(EncodedValues);
	
	return BoolComponentInstancedStruct;
}
