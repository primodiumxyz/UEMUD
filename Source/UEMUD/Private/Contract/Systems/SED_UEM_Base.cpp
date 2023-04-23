// Fill out your copyright notice in the Description page of Project Settings.


#include "Contract/Systems/SED_UEM_Base.h"

#include "Keccak256Helper.h"


const FString USED_UEM_Base::GetEncodedArguments(FInstancedStruct SystemArgumentsStruct)
{
	throw;
}

const TArray<FString> USED_UEM_Base::GetStringArguments(FInstancedStruct SystemArgumentsStruct)
{
	throw;
}

const FString USED_UEM_Base::GetFunctionToExecute()
{
	return "executeTyped(bytes)";
}

const FString USED_UEM_Base::GetEncodedFunctionToExecute()
{
	const FString Signature = GetFunctionToExecute();
	const FString FunctionHash = UKeccak256Helper::Keccak256(Signature);
	FString FunctionSelector = FunctionHash.Mid(0, 8);
	return FString("0x").Append(FunctionSelector);
}
