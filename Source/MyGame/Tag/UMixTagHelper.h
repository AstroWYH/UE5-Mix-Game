// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UMixTagHelper.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UUMixTagHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FString GetLastNameFromGameplayTag(const FGameplayTag& GameplayTag)
	{
		FString FullTagName = GameplayTag.ToString();

		TArray<FString> TagParts;
		FullTagName.ParseIntoArray(TagParts, TEXT("."), true);

		if (TagParts.Num() > 0)
		{
			return TagParts.Last();
		}

		return FString();
	}

	// TODO: FORCEINLINE
	UFUNCTION(BlueprintCallable)
	static bool IsCommonCamp(const FGameplayTag& TagA, const FGameplayTag& TagB)
	{
		FString StrTagA = TagA.ToString();
		FString StrTagB = TagB.ToString();
		
		if (StrTagA.Contains(TEXT("Red")) && StrTagB.Contains(TEXT("Red")))
		{
			return true;
		}
		else if (StrTagA.Contains(TEXT("Blue")) && StrTagB.Contains(TEXT("Blue")))
		{
			return true;
		}

		return false;
	}
};
