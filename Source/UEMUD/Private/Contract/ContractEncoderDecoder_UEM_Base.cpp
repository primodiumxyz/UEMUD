// Fill out your copyright notice in the Description page of Project Settings.


#include "Contract/ContractEncoderDecoder_UEM_Base.h"
#include "Keccak256.h"
#include "Keccak256Helper.h"

FString UContractEncoderDecoder_UEM_Base::GetIdHex() const 
{
	return UKeccak256Helper::Keccak256(Id);	
}

