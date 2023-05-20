// Fill out your copyright notice in the Description page of Project Settings.


#include "Contract/ParseConfig.h"

#include "Contract/Tables/ParsedTable.h"


void UParseConfig::ParseConfigString(FString Config, FParsedConfig& ParsedConfig, const UObject* WorldContextObject)
{
	TSharedPtr<FJsonValue> JsonValue;
	//Config = Config.Replace(LINE_TERMINATOR,TEXT(""));
	//Config = Config.Replace(TEXT("\t"),TEXT(""));
	//Config = Config.Replace(TEXT(" "),TEXT(""));
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Config);
	
	if(FJsonSerializer::Deserialize(JsonReader, JsonValue))
	{
		const TArray<TSharedPtr<FJsonValue>>* Tables;
		JsonValue->TryGetArray(Tables);


		for(const TSharedPtr<FJsonValue>& Table : *Tables)
		{
			const TSharedPtr<FJsonObject>* TableObject;
			Table->TryGetObject(TableObject);
			
			
			FParsedTable ParsedTable;
			if(TableObject->Get()->HasField("name"))
			{
				FString name = TableObject->Get()->GetStringField("name");
				ParsedTable.TableId = name;	
			}
			
			if( TableObject->Get()->HasField("schema"))
			{
				const auto SchemaObject= TableObject->Get()->GetObjectField("schema");
				const auto SchemaElements = SchemaObject->Values;
				for (auto SchemaElement : SchemaElements)
				{

					EValueTypeSchema FieldType = EValueTypeSchema::Number;
					// switch (SchemaElement.Value->AsString())
					// {
					// 	case "int32":
					// 	case "uint32":
					// 	FieldType = EValueTypeSchema::Number;
					// 		break;
					// 	case "bool":
					// 	FieldType = EValueTypeSchema::Bool;
					// 	default:
					// 		throw;
					// 	break;
					// }
					FString FieldName = SchemaElement.Key;
					ParsedTable.Elements.Add(FParsedTableElement(FieldName,FieldType));
				}	
			}
			ParsedConfig.Tables.Add(ParsedTable);
		}
	}
}
