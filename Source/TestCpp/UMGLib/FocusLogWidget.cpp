// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusLogWidget.h"

void UFocusLogWidgetItem::OnFinishAnimation()
{
	OnEventDispather_FinishAnime.Broadcast(id);
	RemoveFromParent();
}

void UFocusLogWidget::CreateItemLogMessage(UFocusLogWidgetItem* createItemWidget, FString inMessage)
{
	if (VerticalBoxItem == nullptr) return;
	if (m_FocusList.Num() >= 6){RemoveIdMin();} // 古いものを削除
	VerticalBoxItem->AddChildToVerticalBox(createItemWidget);
	m_FocusList.Add(createItemWidget);
	index++;
	createItemWidget->SetRenderScale(FVector2D(1.0f, -1.0f));	
	createItemWidget->id = index;
}



bool UFocusLogWidget::RemoveFocusItemList(int32 idx)
{
	bool retval = false;
	if (m_FocusList.Num() == 0) return false; // 存在しない

	UFocusLogWidgetItem* romovewidget = nullptr;
	for (int32 i = 0; i < m_FocusList.Num(); ++i)
	{
		if (m_FocusList[i]->id == idx)
		{
			romovewidget = m_FocusList[i];
			break;
		}
	}
	if (romovewidget != nullptr) {
		m_FocusList.Remove(romovewidget);
		romovewidget->RemoveFromParent(); // ここでやる

	}
	return retval;
}

void UFocusLogWidget::RemoveIdMin()
{
	if (index == 0 || m_FocusList.Num() == 0) return; // 存在しない

	// 古いものを削除する
	// 一番IDが小さいもの
	int32 minid = index;
	for (int32 ji = 0; ji < m_FocusList.Num(); ji++)
	{
		if (m_FocusList[ji]->id < minid)
		{
			minid = m_FocusList[ji]->id;
		}
	}
	RemoveFocusItemList(index);
}
