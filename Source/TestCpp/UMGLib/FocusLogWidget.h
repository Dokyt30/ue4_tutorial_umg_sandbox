// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"

#include "FocusLogWidget.generated.h"


/**
 *
 */
UCLASS()
class TESTCPP_API UFocusLogWidgetItem : public UUserWidget
{
	GENERATED_BODY()

};


/**
 * 
 */
UCLASS()
class TESTCPP_API UFocusLogWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "FocusLogWidget")
	/// <summary>
	/// メッセージItem追加
	/// </summary>
	void CreateItemLogMessage();


	UFUNCTION(BlueprintCallable, Category = "FocusLogWidget")
	void SetVerticalBox(UVerticalBox* inVerticalBoxItem) {
		VerticalBoxItem = inVerticalBoxItem;
	}


	UVerticalBox* VerticalBoxItem;
};
