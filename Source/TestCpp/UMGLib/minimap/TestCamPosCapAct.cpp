// Fill out your copyright notice in the Description page of Project Settings.

#include "TestCamPosCapAct.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetRenderingLibrary.h"

#include "Kismet/GameplayStatics.h"



class ATestCamPosCapActController
{


public:

	ATestCamPosCapActController(ATestCamPosCapAct& owner, float inWidthOrtho)
		:owner(owner)
	{
		
		TArray<FVector2D> a;
		TArray<FVector2D> b;
		TArray<FVector2D> c;

		a.Add(FVector2D( inWidthOrtho, -inWidthOrtho));
		a.Add(FVector2D(			0, -inWidthOrtho));
		a.Add(FVector2D(-inWidthOrtho, -inWidthOrtho));
		b.Add(FVector2D( inWidthOrtho,			   0));
		b.Add(FVector2D(			0,			   0));
		b.Add(FVector2D(-inWidthOrtho,			   0));
		c.Add(FVector2D( inWidthOrtho,  inWidthOrtho));
		c.Add(FVector2D(			0,  inWidthOrtho));
		c.Add(FVector2D(-inWidthOrtho,  inWidthOrtho));

		posarray.Add(a);
		posarray.Add(b);
		posarray.Add(c);

	}
	static void Convert2Position3(const FVector& pos, FVector2D& output){
		output.X = pos.Y;
		output.Y = -pos.X;
	}
	static void Convert2Position2(const FVector2D& pos, FVector2D& output){
		output.X = pos.Y;
		output.Y = -pos.X;
	}
	static FVector2D SConvert2Position(const FVector& pos) {
		FVector2D output; 
		output.X = pos.Y;
		output.Y = -pos.X;
		return output;
	}
	static FVector2D SConvert2Position2(const FVector2D& pos) {
		FVector2D output;
		output.X = pos.Y;
		output.Y = -pos.X;
		return output;
	}

	static int32 GetPositionX(int32 id) {
		return (int32)(id % 3);
	}
	static int32 GetPositionY(int32 id) {
		return (int32)(id / 3);
	}

	FVector2D& GetPositionId(int32 id) {
		int32 x = ATestCamPosCapActController::GetPositionX(id);
		int32 y = ATestCamPosCapActController::GetPositionY(id);
		return posarray[x][y];
	}

	ATestCamPosCapAct& owner;
	TArray<TArray<FVector2D>> posarray;

	
	// -------------------------------

	int32 GetNowPosition(float warizanritu = 1.0f)
	{
		
		FVector actoorPos;
		APawn* playerActPawn = UGameplayStatics::GetPlayerPawn(owner.GetWorld(), 0);
		if (playerActPawn != nullptr) {
			actoorPos = playerActPawn->GetActorLocation();
		}
		//FVector capturePos = owner.GetActorLocation();
		FVector capturePos = owner.GetActorLocation();

		FVector2D imageIdPos;

		imageIdPos.Y = actoorPos.X - capturePos.X;
		imageIdPos.Y *= -1.0f;
		imageIdPos.X = actoorPos.Y - capturePos.Y;

		// 現在9か所の場所特定 0~9
		/*
		UMG 0から開始

		0─1─2
		│ │ │
		3─4─5
		│ │ │
		6─7─8

		左上からの座標 1024のBOXならば

		512の境界でいけるはず


		 ─ -512,-512     ─     0,-512    -     512,-512
		  |                     |                |
		 ─ -512,0        ─     0,0       ─     512,0
		  |                     |                |
		 ─-512,512      ─     0, 512    ─     512,512

		*/
		int32 pos = 4;// 中央


		const float widthhalf = (owner.GetOrthofWidth()*warizanritu) / 2.0f;

		if (imageIdPos.X <= -widthhalf 
			&& imageIdPos.Y <= -widthhalf) {
			pos = 0;
		}
		else if (-widthhalf < imageIdPos.X && imageIdPos.X <= widthhalf 
			&& imageIdPos.Y <= -widthhalf) {
			pos = 1;
		}
		else if (widthhalf < imageIdPos.X 
			&& imageIdPos.Y <= -widthhalf) {
			pos = 2;
		}
		else if (widthhalf <= -imageIdPos.X 
			&& -widthhalf < imageIdPos.Y && imageIdPos.Y <= widthhalf) {
			pos = 3;
		}
		else if (-widthhalf < imageIdPos.X && imageIdPos.X <= widthhalf 
			&& -widthhalf < imageIdPos.Y && imageIdPos.Y <= widthhalf) {
			pos = 4;
		}
		else if (widthhalf < imageIdPos.X 
			&& -widthhalf < imageIdPos.Y && imageIdPos.Y <= widthhalf) {
			pos = 5;
		}
		else if (imageIdPos.X <= -widthhalf
			&& widthhalf < imageIdPos.Y) {
			pos = 6;
		}
		else if (-widthhalf < imageIdPos.X && imageIdPos.X <= widthhalf
			&& widthhalf < imageIdPos.Y ) {
			pos = 7;
		}
		else if (widthhalf < imageIdPos.X
			&& widthhalf < imageIdPos.Y) {
			pos = 8;
		}

		return pos;
	}
	bool SwapingPoint(TArray<FCST_CamPosImagePositionId>& imageIdPositionList, TArray<bool>& captureFlagList, int32& nowpos, FVector& MovePos)
	{
		
		TArray<FCST_CamPosImagePositionId> previous = imageIdPositionList;
	
		captureFlagList.SetNum(9);

		TArray<bool> tmpCaptureFlagList;
		tmpCaptureFlagList.SetNum(9);

		nowpos = GetNowPosition(1.0f);
		if (nowpos == 4) {
			return false;
		}

		TArray<int32> nextWidgetIdList;
		switch (nowpos) {
		case 0:
		{
			nextWidgetIdList.Add(8);			nextWidgetIdList.Add(5);			nextWidgetIdList.Add(2);
			nextWidgetIdList.Add(7);			nextWidgetIdList.Add(0);			nextWidgetIdList.Add(1);
			nextWidgetIdList.Add(6);			nextWidgetIdList.Add(3);			nextWidgetIdList.Add(4);
			tmpCaptureFlagList[previous[8].id] = true;			tmpCaptureFlagList[previous[5].id] = true;			tmpCaptureFlagList[previous[2].id] = true;
			tmpCaptureFlagList[previous[7].id] = true;			tmpCaptureFlagList[previous[0].id] = false;			tmpCaptureFlagList[previous[1].id] = false;
			tmpCaptureFlagList[previous[6].id] = true;			tmpCaptureFlagList[previous[3].id] = false;			tmpCaptureFlagList[previous[4].id] = false;

		}
		break;
		case 1:
		{
			nextWidgetIdList.Add(6);			nextWidgetIdList.Add(7);			nextWidgetIdList.Add(8);
			nextWidgetIdList.Add(0);			nextWidgetIdList.Add(1);			nextWidgetIdList.Add(2);
			nextWidgetIdList.Add(3);			nextWidgetIdList.Add(4);			nextWidgetIdList.Add(5);

			tmpCaptureFlagList[previous[6].id] = true;			tmpCaptureFlagList[previous[7].id] = true;			tmpCaptureFlagList[previous[8].id] = true;
			tmpCaptureFlagList[previous[0].id] = false;			tmpCaptureFlagList[previous[1].id] = false;			tmpCaptureFlagList[previous[2].id] = false;
			tmpCaptureFlagList[previous[3].id] = false;			tmpCaptureFlagList[previous[4].id] = false;			tmpCaptureFlagList[previous[5].id] = false;

		}
		break;
		case 2:
		{
			nextWidgetIdList.Add(0);			nextWidgetIdList.Add(3);			nextWidgetIdList.Add(6);
			nextWidgetIdList.Add(1);			nextWidgetIdList.Add(2);			nextWidgetIdList.Add(7);
			nextWidgetIdList.Add(4);			nextWidgetIdList.Add(5);			nextWidgetIdList.Add(8);

			tmpCaptureFlagList[previous[0].id] = true;			tmpCaptureFlagList[previous[3].id] = true;			tmpCaptureFlagList[previous[6].id] = true;
			tmpCaptureFlagList[previous[1].id] = false;			tmpCaptureFlagList[previous[2].id] = false;			tmpCaptureFlagList[previous[7].id] = true;
			tmpCaptureFlagList[previous[4].id] = false;			tmpCaptureFlagList[previous[5].id] = false;			tmpCaptureFlagList[previous[8].id] = true;
		}
		break;
		case 3:
		{
			nextWidgetIdList.Add(2);			nextWidgetIdList.Add(0);			nextWidgetIdList.Add(1);
			nextWidgetIdList.Add(5);			nextWidgetIdList.Add(3);			nextWidgetIdList.Add(4);
			nextWidgetIdList.Add(8);			nextWidgetIdList.Add(6);			nextWidgetIdList.Add(7);

			tmpCaptureFlagList[previous[2].id] = true;		tmpCaptureFlagList[previous[0].id] = false;		tmpCaptureFlagList[previous[1].id] = false;
			tmpCaptureFlagList[previous[5].id] = true;		tmpCaptureFlagList[previous[3].id] = false;		tmpCaptureFlagList[previous[4].id] = false;
			tmpCaptureFlagList[previous[8].id] = true;		tmpCaptureFlagList[previous[6].id] = false;		tmpCaptureFlagList[previous[7].id] = false;
		}
		break;
		case 5:
		{
			nextWidgetIdList.Add(1);			nextWidgetIdList.Add(2);			nextWidgetIdList.Add(0);
			nextWidgetIdList.Add(4);			nextWidgetIdList.Add(5);			nextWidgetIdList.Add(3);
			nextWidgetIdList.Add(7);			nextWidgetIdList.Add(8);			nextWidgetIdList.Add(6);


			tmpCaptureFlagList[previous[1].id] = false;		tmpCaptureFlagList[previous[2].id] = false;		tmpCaptureFlagList[previous[0].id] = true;
			tmpCaptureFlagList[previous[4].id] = false;		tmpCaptureFlagList[previous[5].id] = false;		tmpCaptureFlagList[previous[3].id] = true;
			tmpCaptureFlagList[previous[7].id] = false;		tmpCaptureFlagList[previous[8].id] = false;		tmpCaptureFlagList[previous[6].id] = true;

		}
		break;
		case 6:
		{
			nextWidgetIdList.Add(0);			nextWidgetIdList.Add(3);			nextWidgetIdList.Add(4);
			nextWidgetIdList.Add(1);			nextWidgetIdList.Add(6);			nextWidgetIdList.Add(7);
			nextWidgetIdList.Add(2);			nextWidgetIdList.Add(5);			nextWidgetIdList.Add(8);

			tmpCaptureFlagList[previous[0].id] = true;			tmpCaptureFlagList[previous[3].id] = false;			tmpCaptureFlagList[previous[4].id] = false;
			tmpCaptureFlagList[previous[1].id] = true;			tmpCaptureFlagList[previous[6].id] = false;			tmpCaptureFlagList[previous[7].id] = false;
			tmpCaptureFlagList[previous[2].id] = true;			tmpCaptureFlagList[previous[5].id] = true;			tmpCaptureFlagList[previous[8].id] = true;

		}
		break;
		case 7:
		{
			nextWidgetIdList.Add(3);			nextWidgetIdList.Add(4);			nextWidgetIdList.Add(5);
			nextWidgetIdList.Add(6);			nextWidgetIdList.Add(7);			nextWidgetIdList.Add(8);
			nextWidgetIdList.Add(0);			nextWidgetIdList.Add(1);			nextWidgetIdList.Add(2);

			tmpCaptureFlagList[previous[3].id] = false;			tmpCaptureFlagList[previous[4].id] = false;			tmpCaptureFlagList[previous[5].id] = false;
			tmpCaptureFlagList[previous[6].id] = false;			tmpCaptureFlagList[previous[7].id] = false;			tmpCaptureFlagList[previous[8].id] = false;
			tmpCaptureFlagList[previous[0].id] = true;			tmpCaptureFlagList[previous[1].id] = true;			tmpCaptureFlagList[previous[2].id] = true;
		}
		break;
		case 8:
		{
			nextWidgetIdList.Add(4);			nextWidgetIdList.Add(5);			nextWidgetIdList.Add(2);
			nextWidgetIdList.Add(7);			nextWidgetIdList.Add(8);			nextWidgetIdList.Add(1);
			nextWidgetIdList.Add(6);			nextWidgetIdList.Add(3);			nextWidgetIdList.Add(0);

			tmpCaptureFlagList[previous[4].id] = false;			tmpCaptureFlagList[previous[5].id] = false;			tmpCaptureFlagList[previous[2].id] = true;
			tmpCaptureFlagList[previous[7].id] = false;			tmpCaptureFlagList[previous[8].id] = false;			tmpCaptureFlagList[previous[1].id] = true;
			tmpCaptureFlagList[previous[6].id] = true;			tmpCaptureFlagList[previous[3].id] = true;			tmpCaptureFlagList[previous[0].id] = true;


		}
		break;

		}

		FString debugstr = "";
		debugstr.AppendInt(nowpos);
		for (int i = 0; i < 9; ++i) {
			//debugstr.Append(FString::Format(TEXT("%d, %d _ "), { imageIdPositionList[i].id,previous[nextWidgetIdList[i]].id }));
			debugstr.Append(": ");
			debugstr.AppendInt(imageIdPositionList[i].id);
			debugstr.Append(",");
			debugstr.AppendInt(previous[nextWidgetIdList[i]].id);
			imageIdPositionList[i].id = previous[nextWidgetIdList[i]].id;
			imageIdPositionList[i].renderTargetId = previous[nextWidgetIdList[i]].renderTargetId;
			imageIdPositionList[i].Position = previous[nextWidgetIdList[i]].Position;
			captureFlagList[i] = tmpCaptureFlagList[i];
			//debugstr.Append(" , ");
			//debugstr.AppendInt(imageIdPositionList[i].id);
			//debugstr.AppendInt(captureFlagList[i]);
		}

		UE_LOG(LogTemp, Warning, TEXT("SwapingPoint %s --"), *debugstr);

		FVector2D& tmppos = GetPositionId(nowpos);
		MovePos += FVector(tmppos.X, tmppos.Y, .0f);

		return true;
	}


};




ATestCamPosCapAct::ATestCamPosCapAct(const FObjectInitializer& ObjectInitializer)
{
	bInitSetCenterCameraPos = false;
	orthoWidth = 512.0f;
	widgetImageSize = 256.0f;
	prevHalfCapturePos = 4;
}

void ATestCamPosCapAct::BeginPlay() {
	Super::BeginPlay();
	controller = MakeShared< ATestCamPosCapActController>(*this, orthoWidth); // Ortho Width
	imageIdPositionList.SetNum(9);// 9固定
	for (int32 i = 0; i < imageIdPositionList.Num(); ++i) {
		imageIdPositionList[i].id = i;
		imageIdPositionList[i].renderTargetId = i;
	}
}


bool ATestCamPosCapAct::OnCapture()
{
	//UE_LOG(LogTemp, Warning, TEXT("ATestCamPosCapAct::OnCapture s ---"));
	USceneCaptureComponent2D* cpcomp = GetCaptureComponent2D();

	TArray<bool> CaptureFlag;
	int32 nextpos=4;

	//TArray<int32> TargetIdList;
	//for (int32 i = 0; i < imageIdPositionList.Num(); ++i)
	//{
	//	TargetIdList.Add(imageIdPositionList[i].id);
	//}

	//{
	//	FString debugstr = "";
	//	for (int i = 0; i < 9; ++i) {
	//		debugstr.AppendInt(imageIdPositionList[i].id);
	//		debugstr.Append(",");
	//	}
	//	UE_LOG(LogTemp, Warning, TEXT("capture1 %s "), *debugstr);
	//}

	SetCameraCenterPlayerPosition();
	FVector initPos = CameraCenterPlayerPosition;//initPos = GetActorLocation();

	if (controller->SwapingPoint(imageIdPositionList, CaptureFlag, nextpos, CameraCenterPlayerPosition))
	{

		//{
		//	FString debugstr = "";
		//	for (int i = 0; i < 9; ++i) {
		//		debugstr.AppendInt(imageIdPositionList[i].id);
		//		debugstr.Append(",");
		//	}
		//	UE_LOG(LogTemp, Warning, TEXT("capture2 %s "), *debugstr);
		//}
		FVector2D& vposnext = controller->GetPositionId(nextpos);// 5の位置は4の位置なのでOK

		for (int32 i = 0; i < TextureRenderTarget2DList.Num(); ++i)
		{
			// ターゲットは変えない前の位置を更新する。つまりマテリアルとBakeする位置、Instanceは同じ位置。
			// （そのため、UMGの描画位置をチェンジすればOK
			const int32 renderTargetId = imageIdPositionList[i].renderTargetId;
			const int32 targetId = imageIdPositionList[i].id;
			auto target = TextureRenderTarget2DList[renderTargetId];
			if (!IsValid(target))continue;

			FVector2D& vpos = controller->GetPositionId(i);// 5の位置は4の位置なのでOK
			FVector vec = initPos + FVector(vpos.X + vposnext.X, vpos.Y+ vposnext.Y, 500.0f);
			//vec = initPos;
			cpcomp->SetWorldLocation(vec);

			FString debugstr = "";

			debugstr.Append(cpcomp->TextureTarget->GetPathName() + " to " + target->GetPathName() + " : ");
			cpcomp->TextureTarget = target;
			debugstr.Append(cpcomp->TextureTarget->GetPathName() + " to " + target->GetPathName() + " : ");
			if (CaptureFlag[targetId]) {
				debugstr.AppendInt(targetId);
				debugstr.Append(",");
				debugstr.AppendInt(renderTargetId);
				cpcomp->CaptureScene();
				UKismetRenderingLibrary::DrawMaterialToRenderTarget(this, TextureRenderTarget2DBakeList[renderTargetId], MaterialInstanceList[renderTargetId]);
				UE_LOG(LogTemp, Warning, TEXT("capture %s "), *debugstr);
			}
		}

		this->SetActorLocation(CameraCenterPlayerPosition);
	}
	else {
		// 外れていないとき
		int32 nowpos = controller->GetNowPosition(0.5f);
		
		if (nowpos != 4 && prevHalfCapturePos != nowpos) {
			switch (nowpos) {
			case 0:
			{
				CaptureFlag[imageIdPositionList[0].id] = true;			CaptureFlag[imageIdPositionList[1].id] = true;			CaptureFlag[imageIdPositionList[2].id] = true;
				CaptureFlag[imageIdPositionList[3].id] = true;			CaptureFlag[imageIdPositionList[4].id] = false;			CaptureFlag[imageIdPositionList[5].id] = false;
				CaptureFlag[imageIdPositionList[6].id] = true;			CaptureFlag[imageIdPositionList[7].id] = false;			CaptureFlag[imageIdPositionList[8].id] = false;

			}
			break;
			case 1:
			{
				CaptureFlag[imageIdPositionList[0].id] = true;			CaptureFlag[imageIdPositionList[1].id] = true;			CaptureFlag[imageIdPositionList[2].id] = true;
				CaptureFlag[imageIdPositionList[3].id] = false;			CaptureFlag[imageIdPositionList[4].id] = false;			CaptureFlag[imageIdPositionList[5].id] = false;
				CaptureFlag[imageIdPositionList[6].id] = false;			CaptureFlag[imageIdPositionList[7].id] = false;			CaptureFlag[imageIdPositionList[8].id] = false;

			}
			break;
			case 2:
			{
				CaptureFlag[imageIdPositionList[0].id] = true;			CaptureFlag[imageIdPositionList[1].id] = true;			CaptureFlag[imageIdPositionList[2].id] = true;
				CaptureFlag[imageIdPositionList[3].id] = false;			CaptureFlag[imageIdPositionList[4].id] = false;			CaptureFlag[imageIdPositionList[5].id] = true;
				CaptureFlag[imageIdPositionList[6].id] = false;			CaptureFlag[imageIdPositionList[7].id] = false;			CaptureFlag[imageIdPositionList[8].id] = true;
			}
			break;
			case 3:
			{
				CaptureFlag[imageIdPositionList[0].id] = true;		CaptureFlag[imageIdPositionList[1].id] = false;		CaptureFlag[imageIdPositionList[2].id] = false;
				CaptureFlag[imageIdPositionList[3].id] = true;		CaptureFlag[imageIdPositionList[4].id] = false;		CaptureFlag[imageIdPositionList[5].id] = false;
				CaptureFlag[imageIdPositionList[6].id] = true;		CaptureFlag[imageIdPositionList[7].id] = false;		CaptureFlag[imageIdPositionList[8].id] = false;
			}
			break;
			case 5:
			{
				CaptureFlag[imageIdPositionList[0].id] = false;		CaptureFlag[imageIdPositionList[1].id] = false;		CaptureFlag[imageIdPositionList[2].id] = true;
				CaptureFlag[imageIdPositionList[3].id] = false;		CaptureFlag[imageIdPositionList[4].id] = false;		CaptureFlag[imageIdPositionList[5].id] = true;
				CaptureFlag[imageIdPositionList[6].id] = false;		CaptureFlag[imageIdPositionList[7].id] = false;		CaptureFlag[imageIdPositionList[8].id] = true;

			}
			break;
			case 6:
			{
				CaptureFlag[imageIdPositionList[0].id] = true;			CaptureFlag[imageIdPositionList[1].id] = false;			CaptureFlag[imageIdPositionList[2].id] = false;
				CaptureFlag[imageIdPositionList[3].id] = true;			CaptureFlag[imageIdPositionList[4].id] = false;			CaptureFlag[imageIdPositionList[5].id] = false;
				CaptureFlag[imageIdPositionList[6].id] = true;			CaptureFlag[imageIdPositionList[7].id] = true;			CaptureFlag[imageIdPositionList[8].id] = true;

			}
			break;
			case 7:
			{
				CaptureFlag[imageIdPositionList[0].id] = false;			CaptureFlag[imageIdPositionList[1].id] = false;			CaptureFlag[imageIdPositionList[2].id] = false;
				CaptureFlag[imageIdPositionList[3].id] = false;			CaptureFlag[imageIdPositionList[4].id] = false;			CaptureFlag[imageIdPositionList[5].id] = false;
				CaptureFlag[imageIdPositionList[6].id] = true;			CaptureFlag[imageIdPositionList[7].id] = true;			CaptureFlag[imageIdPositionList[8].id] = true;
			}
			break;
			case 8:
			{
				CaptureFlag[imageIdPositionList[0].id] = false;			CaptureFlag[imageIdPositionList[1].id] = false;			CaptureFlag[imageIdPositionList[2].id] = true;
				CaptureFlag[imageIdPositionList[3].id] = false;			CaptureFlag[imageIdPositionList[4].id] = false;			CaptureFlag[imageIdPositionList[5].id] = true;
				CaptureFlag[imageIdPositionList[6].id] = true;			CaptureFlag[imageIdPositionList[7].id] = true;			CaptureFlag[imageIdPositionList[8].id] = true;


			}
			break;

			}

			for (int32 i = 0; i < imageIdPositionList.Num(); ++i)
			{
				const int32 renderTargetId = imageIdPositionList[i].renderTargetId;
				const int32 targetId = imageIdPositionList[i].id;
				auto target = TextureRenderTarget2DList[renderTargetId];
				if (!IsValid(target))continue;
				if (CaptureFlag[targetId]) {
					FString debugstr = "";
					FVector2D& vpos = controller->GetPositionId(i);// 5の位置は4の位置なのでOK
					FVector vec = initPos + FVector(vpos.X, vpos.Y, 500.0f);
					cpcomp->SetWorldLocation(vec);
					cpcomp->TextureTarget = target;
					cpcomp->CaptureScene();
					debugstr.AppendInt(targetId);
					debugstr.Append(":"+ cpcomp->TextureTarget->GetPathName());
					UE_LOG(LogTemp, Warning, TEXT("capture h %s "), *debugstr);
					UKismetRenderingLibrary::DrawMaterialToRenderTarget(this, TextureRenderTarget2DBakeList[renderTargetId], MaterialInstanceList[renderTargetId]);
				}
			}
			prevHalfCapturePos = nowpos;
		}
	}
	return true;
	//UE_LOG(LogTemp, Warning, TEXT("ATestCamPosCapAct::OnCapture e ---"));
}


void ATestCamPosCapAct::OnCaptureAll()
{
	//UE_LOG(LogTemp, Warning, TEXT("ATestCamPosCapAct::OnCapture s ---"));
	USceneCaptureComponent2D* cpcomp = GetCaptureComponent2D();


	SetCameraCenterPlayerPosition();

	TArray<bool> CaptureFlag;
	int32 nextpos = 4;
	FVector initPos = CameraCenterPlayerPosition;//initPos = GetActorLocation();
	bool ret = controller->SwapingPoint(imageIdPositionList, CaptureFlag, nextpos, CameraCenterPlayerPosition);


	for (int32 i = 0; i < TextureRenderTarget2DList.Num(); ++i)
	{
		const int32 targetId = imageIdPositionList[i].id;
		auto target = TextureRenderTarget2DList[targetId];
		if (!IsValid(target))continue;

		FVector2D& vpos = controller->GetPositionId(targetId);
		FVector vec = initPos + FVector(vpos.X, vpos.Y, 500.0f);
		//vec = initPos;
		cpcomp->SetWorldLocation(vec);

		cpcomp->TextureTarget = target;

		cpcomp->CaptureScene();

		//if (nextpos == i) {
		//	CameraCenterPlayerPosition = vec;
		//}
	}
	this->SetActorLocation(CameraCenterPlayerPosition);

	OnBake();
	//UE_LOG(LogTemp, Warning, TEXT("ATestCamPosCapAct::OnCapture e ---"));
}


void ATestCamPosCapAct::OnBake()
{
	for (int32 i = 0; i < TextureRenderTarget2DBakeList.Num(); ++i)
	{

		UKismetRenderingLibrary::DrawMaterialToRenderTarget(this, TextureRenderTarget2DBakeList[i], MaterialInstanceList[i]);
	}
}


void ATestCamPosCapAct::UpdateImagePos()
{
	//UE_LOG(LogTemp, Warning, TEXT("ATestCamPosCapAct:: GetWidgetPositionList s --- "));

	const uint8 imagecount = imageIdPositionList.Num();
	const float widgetSize = widgetImageSize; // Imageのサイズ
	APawn* playerActPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	if (playerActPawn == nullptr)return;
	
	FVector tmpPosSabun= CameraCenterPlayerPosition - (playerActPawn->GetActorLocation());

	TArray<FVector2D> imagewidgetPosition;
	imagewidgetPosition.Add(FVector2D(-widgetSize, -widgetSize));
	imagewidgetPosition.Add(FVector2D(			0, -widgetSize));
	imagewidgetPosition.Add(FVector2D( widgetSize, -widgetSize));
	imagewidgetPosition.Add(FVector2D(-widgetSize,			 0));
	imagewidgetPosition.Add(FVector2D(			0,			 0));
	imagewidgetPosition.Add(FVector2D( widgetSize,			 0));
	imagewidgetPosition.Add(FVector2D(-widgetSize,  widgetSize));
	imagewidgetPosition.Add(FVector2D(			0,  widgetSize));
	imagewidgetPosition.Add(FVector2D( widgetSize,  widgetSize));

	const float widthhiritu = (orthoWidth / (widgetSize));
	
	//FString debugstr = "";
	for (int32 i = 0; i < imagecount; ++i) {
		float _x = tmpPosSabun.X;
		float _y = tmpPosSabun.Y;
		_x *= -1.0f;
		FVector2D t(_y, _x);
		t /= widthhiritu;
		FVector2D& tp = imagewidgetPosition[i];// 4の位置は５になる 4番目の左上にする。
		t.X += tp.X;
		t.Y += tp.Y;
		imageIdPositionList[i].Position = t; // 4番目の位置情報は（５のキャプチャ位置）
		//debugstr.AppendInt(imageIdPositionList[i].id);
		//debugstr.Append(", ");
		//debugstr.Append(": "+t.ToString());
	}

	//UE_LOG(LogTemp, Warning, TEXT("campos %s "), *debugstr);
	//UE_LOG(LogTemp, Warning, TEXT("SwapingPoint %s --"), *debugstr);

}

void ATestCamPosCapAct::SetCameraCenterPlayerPosition()
{
	//if (bInitSetCenterCameraPos)return;

	APawn* playerActPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	if (playerActPawn != nullptr) {
		PlayerActorPosition = playerActPawn->GetActorLocation();
		bInitSetCenterCameraPos = true;
	}
}