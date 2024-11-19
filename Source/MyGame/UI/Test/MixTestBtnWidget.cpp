// Fill out your copyright notice in the Description page of Project Settings.


#include "MixTestBtnWidget.h"

void UMixTestBtnWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ensure(BtnAdd)) return;
	if (!ensure(BtnRemove)) return;
}