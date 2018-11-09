// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestCamPosUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UTestCamPosUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(Category = "TestCamPosUserWidget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AUCL_CamPosSceneCap2DAct* CaptureCam;

public:
	UFUNCTION(BlueprintCallable, Category = "TestCamPosUserWidget")
	void SetCaptureCam(AUCL_CamPosSceneCap2DAct* icapcam) 
	{
		CaptureCam = icapcam;
	}

	UFUNCTION(BlueprintPure, Category = "TestCamPosUserWidget")
	AUCL_CamPosSceneCap2DAct* GetCaptureCam() {
		return CaptureCam;
	}


};
