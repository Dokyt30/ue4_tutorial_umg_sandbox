// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGCppCreate.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetTree.h"





void UUMGCppCreate::CreateImageList()
{
	if (WidgetTree) {
		UCanvasPanel* RootCanvas = Cast<UCanvasPanel>(GetWidgetFromName("CanvasPanel_0"));
		MyCanvas2 = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("CanvasPanel1"));
		RootCanvas->AddChildToCanvas(MyCanvas2);
		{
			UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(MyCanvas2->Slot);
			if (CanvasPanelSlot) {
				CanvasPanelSlot->SetPosition(FVector2D(1340, 520));
				CanvasPanelSlot->SetSize(FVector2D(300, 300));
			}
		}

		for (int32 i = 0; i < 9; ++i) {
			FString fimgname = FString::Printf(TEXT("Image%d"), i);
			UImage* _img = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *fimgname);
			MyCanvas2->AddChildToCanvas(_img);
			ImageList.Add(_img);
			{
				UCanvasPanelSlot* CanvasPanelSlot2 = Cast<UCanvasPanelSlot>(_img->Slot);
				if (CanvasPanelSlot2) {
					FAnchors fanch;
					fanch.Minimum = FVector2D(0.5f, 0.5f);
					fanch.Maximum = FVector2D(0.5f, 0.5f);
					CanvasPanelSlot2->SetAnchors(fanch);
					CanvasPanelSlot2->SetAlignment(FVector2D(0.5f, 0.5f));
					CanvasPanelSlot2->SetPosition(FVector2D(0, 0));
					CanvasPanelSlot2->SetSize(FVector2D(300, 300));
				}
			}
		}
	}
}