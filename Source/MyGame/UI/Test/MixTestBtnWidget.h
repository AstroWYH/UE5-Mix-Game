// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MixTestBtnWidget.generated.h"

/**
 * 该类目前没有使用
 * 非必要不创建UMG的Cpp父类，除非是包裹类复杂的UMG，需要U版和S版的Native实现
 */
UCLASS()
class MYGAME_API UMixTestBtnWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<class UButton> BtnAdd;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<class UButton> BtnRemove;
};
