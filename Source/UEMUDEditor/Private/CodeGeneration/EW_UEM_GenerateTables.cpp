// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeGeneration/EW_UEM_GenerateTables.h"

#include "Contract/Tables/DS_UEM_MudTableConfig.h"
#include "Contract/Tables/ParsedTable.h"




void UEW_UEM_GenerateTables::GenerateTables()
{

	
	const UDS_UEM_MudTableConfig* MudTableConfig = GetDefault<UDS_UEM_MudTableConfig>();

	FString TableDefsSourceDir = FPaths::GameSourceDir() + MudTableConfig->SourceDirSubDir;
	
	FString TableComponentHeaderTemplate;
	if(!FFileHelper::LoadFileToString(TableComponentHeaderTemplate,*MudTableConfig->TableComponentHeaderPath))
		throw;

	FString TableComponentCppTemplate;
	if(!FFileHelper::LoadFileToString(TableComponentCppTemplate,*MudTableConfig->TableComponentCppPath))
		throw;


	TMap<EValueTypeSchema,FString> TableComponentValueTypeTemplates;
	for (auto ValueTypeTemplatePath : MudTableConfig->ValueTypeTemplatePaths)
	{
		FString ValueTypeTemplate;
		if(!FFileHelper::LoadFileToString(ValueTypeTemplate,*ValueTypeTemplatePath.Value))
			throw;
		TableComponentValueTypeTemplates.Add(ValueTypeTemplatePath.Key,ValueTypeTemplate);
	}

	
	
	

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	
	for (const FParsedTable Table : MudTableConfig->Tables)
	{
		FString TableFields;
		for (auto TableElement : Table.Elements)
		{
			FString TableElementField = TableComponentValueTypeTemplates[TableElement.Type];
			TableFields += TableElementField.Replace(TEXT("%VALUE_NAME%"),*TableElement.Name);
		}

		FString TableHeader = TableComponentHeaderTemplate;
		FString TableStructName = Table.TableId;
		TableHeader = TableHeader.Replace(TEXT("%UNPREFIXED_CLASS_NAME%"),*TableStructName);
		TableHeader = TableHeader.Replace(TEXT("%CLASS_MODULE_API_MACRO%"),*MudTableConfig->ClassModuleAPIMacro);
		TableHeader = TableHeader.Replace(TEXT("%COLUMNS%"),*TableFields);
		
		FString file = TableDefsSourceDir;
		file.Append(Table.TableId+TEXT(".h"));
		if(!FFileHelper::SaveStringToFile(TableHeader,*file))
			throw;
		
		FString TableCpp = TableComponentCppTemplate;
		TableCpp = TableCpp.Replace(TEXT("%PATH_TO_HEADER%"),*file);

		
		file = TableDefsSourceDir;
		file.Append(Table.TableId+TEXT(".cpp"));
		if(!FFileHelper::SaveStringToFile(TableCpp,*file))
			throw;
	}
	
	
}
