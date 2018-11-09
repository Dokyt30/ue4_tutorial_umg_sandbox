// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "Engine/TextureRenderTarget2D.h"
//#include "Components/Image.h"
#include "Components/Widget.h"
#include "TestCamPosCapAct.generated.h"

USTRUCT(BlueprintType)
struct FCST_CamPosImagePositionId {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 renderTargetId; // material instance targetid ŒÅ’è
};

class ATestCamPosCapActController;

/**
 * 
 */
UCLASS()
class UEPROJECT_API ATestCamPosCapAct : public ASceneCapture2D
{
	GENERATED_BODY()

private:
	/** TargetTexture2D */
	UPROPERTY(Category = "CamPosSceneCapture2D", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UTextureRenderTarget2D*> TextureRenderTarget2DList;
	/** TargetTexture2D Bake */
	UPROPERTY(Category = "CamPosSceneCapture2D", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UTextureRenderTarget2D*> TextureRenderTarget2DBakeList;
	/** MaterialInstance Array */
	UPROPERTY(Category = "CamPosSceneCapture2D", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInstance*> MaterialInstanceList;

	UPROPERTY(Category = "CamPosSceneCapture2D", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector CameraCenterPlayerPosition;

	UPROPERTY(Category = "CamPosSceneCapture2D", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector PlayerActorPosition;

	UPROPERTY(Category = "CamPosSceneCapture2D", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FCST_CamPosImagePositionId> imageIdPositionList;

public:
	//UPROPERTY()
	//UWidget* ScrollMapImage1;

public:
	ATestCamPosCapAct(const FObjectInitializer& ObjectInitializer);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "CamPosSceneCapture2D")
	bool OnCapture();

	UFUNCTION(BlueprintCallable, Category = "CamPosSceneCapture2D")
	void OnCaptureAll();

	UFUNCTION(BlueprintCallable, Category = "CamPosSceneCapture2D")
	void OnBake();

	UFUNCTION(BlueprintCallable, Category = "CamPosSceneCapture2D")
	void UpdateImagePos();

	UFUNCTION(BlueprintPure, Category = "CamPosSceneCapture2D")
	TArray<FCST_CamPosImagePositionId>& GetWidgetPositionList() {
		return imageIdPositionList;
	}
		
	UFUNCTION(BlueprintPure, Category = "CamPosSceneCapture2D")
	float GetOrthofWidth() const {return orthoWidth;}

private:

	void SetCameraCenterPlayerPosition();
	TSharedPtr<ATestCamPosCapActController> controller;

	UPROPERTY(Category = "CamPosSceneCapture2D", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float orthoWidth;

	UPROPERTY(Category = "CamPosSceneCapture2D", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float widgetImageSize;

	bool bInitSetCenterCameraPos;

	int32 prevHalfCapturePos;
};
