// Fill out your copyright notice in the Description page of Project Settings.


#include "Encoding/FL_UEM_Encode.h"

FString UFL_UEM_Encode::EncodeNumber(int32 number)
{
	return FString::Printf(TEXT("%#034x"),number);
}
