// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestCamPosUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTCPP_API UTestCamPosUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(Category = "TestCamPosUserWidget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ATestCamPosCapAct* CaptureCam;

public:
	UFUNCTION(BlueprintCallable, Category = "TestCamPosUserWidget")
	void SetCaptureCam(ATestCamPosCapAct* icapcam) 
	{
		CaptureCam = icapcam;
	}

	UFUNCTION(BlueprintPure, Category = "TestCamPosUserWidget")
	ATestCamPosCapAct* GetCaptureCam() {
		return CaptureCam;
	}


};
