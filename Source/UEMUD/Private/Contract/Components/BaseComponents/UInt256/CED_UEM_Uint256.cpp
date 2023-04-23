// Fill out your copyright notice in the Description page of Project Settings.


#include "Contract/Components/BaseComponents/UInt256/CED_UEM_Uint256.h"

#include "Contract/Components/BaseComponents/UInt256/C_UEM_Uint256.h"
#include "Misc/DefaultValueHelper.h"


FInstancedStruct UCED_UEM_Uint256::GetInitializedComponentInstancedStruct()
{
	FInstancedStruct UInt256;
	UInt256.InitializeAs<FC_UEM_Uint256>();
	return UInt256;
}



FInstancedStruct UCED_UEM_Uint256::GetComponentFromEncodedData(const TArray<uint8>& EncodedValues)
{
		FInstancedStruct UInt256InstancedStruct = GetInitializedComponentInstancedStruct();
    	FC_UEM_Uint256& UInt256 = UInt256InstancedStruct.GetMutable<FC_UEM_Uint256>();
    	UInt256.Value = EncodedValues;
    	
    	return UInt256InstancedStruct;
}
