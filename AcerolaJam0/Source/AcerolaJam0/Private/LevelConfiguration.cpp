// Fill out your copyright notice in the Description page of Project Settings.


//#include <regex>
//#include <filesystem>

#include "Misc/FileHelper.h"
//#include "Misc/Paths.h"
#include "Internationalization/Regex.h"
//#include "CoreMinimal.h"
#include "LevelConfiguration.h"

void ULevelConfiguration::loadConfiguration(FString fileLocation, int32& playerHealth, int& playerDamages, double& ennemySize, bool& spawnBoars, bool& spawnArchers, bool& spawnMedusa, bool& spawnTrees, bool& spawnMandrake, bool& plantsEverywhere)
{

	playerHealth = 6;
	playerDamages = 4;
	ennemySize = 1.;
	spawnBoars = true;
	spawnArchers = true;
	spawnMedusa = true;
	spawnTrees = false;
	spawnMandrake = false;
	plantsEverywhere = false;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*fileLocation))
		return;

	UE_LOG(LogTemp, Warning, TEXT("File found !"));
	FString configuration;
	FFileHelper::LoadFileToString(configuration, *fileLocation);

	FRegexPattern healthPattern("^\\s*playerHealth\\s*=\\s*([0-9]+)\\s*(?:#.*)?$");
	FRegexMatcher healthMatcher(healthPattern, configuration);
	if (healthMatcher.FindNext())
		playerHealth = FCString::Atoi(*healthMatcher.GetCaptureGroup(1));
	
	// TODO: read TOML with regex
}

void ULevelConfiguration::writeConfigurationFileLevel1(FString fileLocation)
{
	// TODO
}

void ULevelConfiguration::writeConfigurationFileLevel2(FString fileLocation)
{
	// TODO
}

void ULevelConfiguration::writeConfigurationFileLevel3(FString fileLocation)
{
	// TODO
}

void ULevelConfiguration::writeConfigurationFileLevel4(FString fileLocation)
{
	// TODO
}
