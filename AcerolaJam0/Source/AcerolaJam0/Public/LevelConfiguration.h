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
		static void loadConfiguration(FString fileLocation, int& level, int& playerHealth, int& playerDamages, bool& playerIllness, double& ennemySize, int& ennemyDamageFactor, bool& ennemyGlitchedTexture, bool& spawnBoars, bool& spawnArchers, bool& spawnMedusa, bool& spawnTrees, bool& spawnMandrake, bool& nuclearTrees);
		
		UFUNCTION(BlueprintCallable, Category = "LevelConfiguration")
		static void writeConfigurationFileLevel1(FString fileLocation);

		UFUNCTION(BlueprintCallable, Category = "LevelConfiguration")
		static void writeConfigurationFileLevel2(FString fileLocation);

		UFUNCTION(BlueprintCallable, Category = "LevelConfiguration")
		static void writeConfigurationFileLevel3(FString fileLocation);

		UFUNCTION(BlueprintCallable, Category = "LevelConfiguration")
		static void writeConfigurationFileLevel4(FString fileLocation);
};
