// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/FileHelper.h"
#include "Internationalization/Regex.h"
#include "LevelConfiguration.h"

static bool stringToBool(const FString& str)
{
	FRegexPattern truePattern("^(?i)true$");
	FRegexMatcher trueMatcher(truePattern, str);
	return trueMatcher.FindNext();
}

void ULevelConfiguration::loadConfiguration(FString fileLocation, int& level, int& playerHealth, int& playerDamages, bool& playerIllness, double& ennemySize, int& ennemyDamageFactor, bool& ennemyGlitchedTexture, bool& spawnBoars, bool& spawnArchers, bool& spawnMedusa, bool& spawnTrees, bool& spawnMandrake, bool& nuclearTrees)
{
	level = 1;

	playerHealth = 6;
	playerDamages = 4;
	playerIllness = false;

	ennemySize = 1.;
	ennemyDamageFactor = 1;
	ennemyGlitchedTexture = false;
	spawnBoars = true;
	spawnArchers = true;
	spawnMedusa = true;
	spawnTrees = false;
	spawnMandrake = false;
	nuclearTrees = false;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*fileLocation))
		return;

	FString configuration;
	FFileHelper::LoadFileToString(configuration, *fileLocation);
	TArray<FString> configurationLines;
	configuration.ParseIntoArrayLines(configurationLines);

	for (FString line : configurationLines)
	{

		FRegexPattern levelPattern("^\\s*level\\s*=\\s*([0-9]+)\\s*(?:#.*)?$");
		FRegexMatcher levelMatcher(levelPattern, line);
		if (levelMatcher.FindNext())
		{
			level = FCString::Atoi(*levelMatcher.GetCaptureGroup(1));
			if (level < 1)
				level = 1;
			else if (level > 4)
				level = 4;
		}

		FRegexPattern healthPattern("^\\s*playerHealth\\s*=\\s*([0-9]+)\\s*(?:#.*)?$");
		FRegexMatcher healthMatcher(healthPattern, line);
		if (healthMatcher.FindNext())
		{
			playerHealth = FCString::Atoi(*healthMatcher.GetCaptureGroup(1));
			if (playerHealth < 1)
				playerHealth = 1;
		}

		FRegexPattern damagePattern("^\\s*playerDamages\\s*=\\s*([0-9]+)\\s*(?:#.*)?$");
		FRegexMatcher damageMatcher(damagePattern, line);
		if (damageMatcher.FindNext())
			playerDamages = FCString::Atoi(*damageMatcher.GetCaptureGroup(1));

		FRegexPattern boarPattern("^\\s*spawnBoars\\s*=\\s*((?i)(?:true)|(?:false)(?-i))\\s*(?:#.*)?$");
		FRegexMatcher boarMatcher(boarPattern, line);
		if (boarMatcher.FindNext())
			spawnBoars = stringToBool(boarMatcher.GetCaptureGroup(1));

		FRegexPattern archerPattern("^\\s*spawnArchers\\s*=\\s*((?i)(?:true)|(?:false)(?-i))\\s*(?:#.*)?$");
		FRegexMatcher archerMatcher(archerPattern, line);
		if (archerMatcher.FindNext())
			spawnArchers = stringToBool(archerMatcher.GetCaptureGroup(1));

		FRegexPattern medusaPattern("^\\s*spawnMedusa\\s*=\\s*((?i)(?:true)|(?:false)(?-i))\\s*(?:#.*)?$");
		FRegexMatcher medusaMatcher(medusaPattern, line);
		if (medusaMatcher.FindNext())
			spawnMedusa = stringToBool(medusaMatcher.GetCaptureGroup(1));

		FRegexPattern treePattern("^\\s*spawnTrees\\s*=\\s*((?i)(?:true)|(?:false)(?-i))\\s*(?:#.*)?$");
		FRegexMatcher treeMatcher(treePattern, line);
		if (treeMatcher.FindNext())
			spawnTrees = stringToBool(treeMatcher.GetCaptureGroup(1));

		FRegexPattern mandrakePattern("^\\s*spawnMandrake\\s*=\\s*((?i)(?:true)|(?:false)(?-i))\\s*(?:#.*)?$");
		FRegexMatcher mandrakeMatcher(mandrakePattern, line);
		if (mandrakeMatcher.FindNext())
		{
			UE_LOG(LogTemp, Warning, TEXT(" !!! mandrake match"));
			spawnMandrake = stringToBool(mandrakeMatcher.GetCaptureGroup(1));
		}

		FRegexPattern nukePattern("^\\s*nuclearTrees\\s*=\\s*((?i)(?:true)|(?:false)(?-i))\\s*(?:#.*)?$");
		FRegexMatcher nukeMatcher(nukePattern, line);
		if (nukeMatcher.FindNext())
			nuclearTrees = stringToBool(nukeMatcher.GetCaptureGroup(1));

		FRegexPattern dopingPattern("^\\s*ennemiesDoping\\s*=\\s*((?i)(?:true)|(?:false)(?-i))\\s*(?:#.*)?$");
		FRegexMatcher dopingMatcher(dopingPattern, line);
		if (dopingMatcher.FindNext())
		{
			bool doping = stringToBool(dopingMatcher.GetCaptureGroup(1));
			if (doping)
			{
				ennemyDamageFactor = 2;
				ennemyGlitchedTexture = true;
			}
			else
			{
				ennemyDamageFactor = 1;
				ennemyGlitchedTexture = false;
			}
		}

		FRegexPattern illnessPattern("^\\s*playerIllness\\s*=\\s*((?i)(?:true)|(?:false)(?-i))\\s*(?:#.*)?$");
		FRegexMatcher illnessMatcher(illnessPattern, line);
		if (illnessMatcher.FindNext())
			playerIllness = stringToBool(illnessMatcher.GetCaptureGroup(1));
	}
}

void ULevelConfiguration::writeConfigurationFileLevel1(FString fileLocation)
{
	FString str =
"[level]\n\
level = 1 # always between 1 and 4\n\
\n\
[player]\n\
playerHealth = 6\n\
playerDamages = 4\n\
\n\
[ennemies]\n\
spawnBoars = true\n\
spawnArchers = true\n\
spawnMedusa = true\n\
spawnTrees = false\n\
spawnMandrake = false # not implemented\n\
nuclearTrees = false\n\
\n\
[experimental]\n\
# The following features have not been tested and may be subject to bugs.\n\
# PLEASE LEAVE THEM TO 'false'.\n\
# Enabling these features is at your own risks.\n\
\n\
ennemiesDoping = false # increase ennemy damages. Untested feature. Must be false.\n\
playerIllness = false # little joke from the developper, which makes the game basically impossible. Must be false.\n\
";
	FFileHelper::SaveStringToFile(str, *fileLocation);
}

void ULevelConfiguration::writeConfigurationFileLevel2(FString fileLocation)
{
	FString str =
"[level]\n\
level = 2 # always between 1 and 4\n\
\n\
[player]\n\
playerHealth = 6\n\
playerDamages = 6\n\
\n\
[ennemies]\n\
spawnBoars = true\n\
spawnArchers = true\n\
spawnMedusa = true\n\
spawnTrees = true\n\
spawnMandrake = true # not implemented\n\
nuclearTrees = false\n\
\n\
[experimental]\n\
# The following features have not been tested and may be subject to bugs.\n\
# PLEASE LEAVE THEM TO 'false'.\n\
# Enabling these features is at your own risks.\n\
\n\
ennemiesDoping = false # increase ennemy damages. Untested feature. Must be false.\n\
playerIllness = false # little joke from the developper, which makes the game basically impossible. Must be false.\n\
";
	FFileHelper::SaveStringToFile(str, *fileLocation);
}

void ULevelConfiguration::writeConfigurationFileLevel3(FString fileLocation)
{
	FString str =
"[level]\n\
level = 3 # always between 1 and 4\n\
\n\
[player]\n\
playerHealth = 9\n\
playerDamages = -999\n\
\n\
[ennemies]\n\
spawnBoars = true\n\
spawnArchers = true\n\
spawnMedusa = true\n\
spawnTrees = true\n\
spawnMandrake = true # not implemented\n\
nuclearTrees = true\n\
\n\
[experimental]\n\
# The following features have not been tested and may be subject to bugs.\n\
# PLEASE LEAVE THEM TO 'false'.\n\
# Enabling these features is at your own risks.\n\
\n\
ennemiesDoping = true # increase ennemy damages. Untested feature. Must be false.\n\
playerIllness = false # little joke from the developper, which makes the game basically impossible. Must be false.\n\
";
	FFileHelper::SaveStringToFile(str, *fileLocation);
}

void ULevelConfiguration::writeConfigurationFileLevel4(FString fileLocation)
{
	FString str =
"[level]\n\
level = 4 # always between 1 and 4\n\
\n\
[player]\n\
playerHealth = 3\n\
playerDamages = -999\n\
\n\
[ennemies]\n\
spawnBoars = true\n\
spawnArchers = true\n\
spawnMedusa = true\n\
spawnTrees = true\n\
spawnMandrake = true # not implemented\n\
nuclearTrees = true\n\
\n\
[experimental]\n\
# The following features have not been tested and may be subject to bugs.\n\
# PLEASE LEAVE THEM TO 'false'.\n\
# Enabling these features is at your own risks.\n\
\n\
ennemiesDoping = true # increase ennemy damages. Untested feature. Must be false.\n\
playerIllness = true # little joke from the developper, which makes the game basically impossible. Must be false.\n\
";
	FFileHelper::SaveStringToFile(str, *fileLocation);
}
