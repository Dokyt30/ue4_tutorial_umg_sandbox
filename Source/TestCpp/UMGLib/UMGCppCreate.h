// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMGCppCreate.generated.h"

/**
 * 
 */
UCLASS()
class TESTCPP_API UUMGCppCreate : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "UMGCppCreate")
		void CreateImageList();

	
protected:
	UPROPERTY(Category = "UMGCppCreate", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UImage*> ImageList;
	UPROPERTY(Category = "UMGCppCreate", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCanvasPanel* MyCanvas2;

};
