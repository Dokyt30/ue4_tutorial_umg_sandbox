// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"

#include "FocusLogWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FocusLogWidgetItemEventDispather, int32, inIdx);

// ----------------------------------------------------------
/** 
 *
 */
UCLASS()
class TESTCPP_API UFocusLogWidgetItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FocusLogWidgetItem")
	void OnFinishAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "FocusLogWidgetItem")
	int32 id;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite,  Category = "FocusLogWidgetItem")
	FocusLogWidgetItemEventDispather OnEventDispather_FinishAnime;
};



// ----------------------------------------------------------
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
	void CreateItemLogMessage(UFocusLogWidgetItem* createItemWidget, FString inMessage);

	UFUNCTION(BlueprintCallable, Category = "FocusLogWidget")
	void SetVerticalBox(UVerticalBox* inVerticalBoxItem) {
		VerticalBoxItem = inVerticalBoxItem;
	}

	UFUNCTION(BlueprintCallable, Category = "FocusLogWidget")
	bool RemoveFocusItemList(int32 idx);

protected:
	void RemoveIdMin();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FocusLogWidget")
	UVerticalBox* VerticalBoxItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FocusLogWidget")
	TArray<UFocusLogWidgetItem*> m_FocusList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FocusLogWidget")
	int32 index;

};

// ----------------------------------------------------------
