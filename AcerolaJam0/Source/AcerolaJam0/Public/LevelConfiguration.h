// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LevelConfiguration.generated.h"

/**
 * 
 */
UCLASS()
class ACEROLAJAM0_API ULevelConfiguration : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category="LevelConfiguration")
		static void loadConfiguration(FString fileLocation, int32& playerHealth, int& playerDamages, double& ennemySize, bool& spawnBoars, bool& spawnArchers, bool& spawnMedusa, bool& spawnTrees, bool& spawnMandrake, bool& plantsEverywhere);
		static void writeConfigurationFileLevel1(FString fileLocation);
		static void writeConfigurationFileLevel2(FString fileLocation);
		static void writeConfigurationFileLevel3(FString fileLocation);
		static void writeConfigurationFileLevel4(FString fileLocation);
};
