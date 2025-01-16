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

	// TODO: FORCEINLINE 废弃
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

	// eg: PathPoint_1->1 废弃
	UFUNCTION(BlueprintCallable)
	static int32 ExtractNumberFromFName(const FName& Name)
	{
		FString NameString = Name.ToString();
		int32 UnderscoreIndex;
		
		if (NameString.FindLastChar(TEXT('_'), UnderscoreIndex))
		{
			FString NumberString = NameString.RightChop(UnderscoreIndex + 1);
			return FCString::Atoi(*NumberString);
		}

		return 0;
	}

	UFUNCTION(BlueprintCallable)
	static int32 ConvertNumberFromFName(const FName& Name)
	{
		FString NameString = Name.ToString();
		return FCString::Atoi(*NameString);
	}
};
