// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseComponents/Coord/CED_UEM_Coord.h"

#include "Components/BaseComponents/Coord/C_UEM_Coord.h"
#include "Encoding/FL_UEM_Encode.h"
#include "Hex/FL_UEM_HexConversions.h"


FInstancedStruct UCED_UEM_Coord::GetInitializedComponentInstancedStruct()
{
	FInstancedStruct CoordComponent;
	CoordComponent.InitializeAs<FC_UEM_Coord>();
	return CoordComponent;
}



FInstancedStruct UCED_UEM_Coord::GetComponentFromEncodedData(const TArray<uint8>& EncodedValues)
{

	
	FInstancedStruct TypedComponent = GetInitializedComponentInstancedStruct();

	FC_UEM_Coord Coord = FC_UEM_Coord(UFL_UEM_Encode::DecodeNumber(EncodedValues),UFL_UEM_Encode::DecodeNumber(EncodedValues,32));
	FInstancedStruct CoordComponent;
	CoordComponent.InitializeAs<FC_UEM_Coord>(Coord);
	
	TypedComponent.InitializeAs(TypedComponent.GetScriptStruct(),CoordComponent.GetMemory());
	return TypedComponent;
}

