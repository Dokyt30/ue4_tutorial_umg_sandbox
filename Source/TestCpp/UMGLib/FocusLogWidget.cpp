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
	if (m_FocusList.Num() >= 6){RemoveIdMin();} // ŒÃ‚¢‚à‚Ì‚ğíœ
	VerticalBoxItem->AddChildToVerticalBox(createItemWidget);
	m_FocusList.Add(createItemWidget);
	index++;
	createItemWidget->SetRenderScale(FVector2D(1.0f, -1.0f));	
	createItemWidget->id = index;
}



bool UFocusLogWidget::RemoveFocusItemList(int32 idx)
{
	bool retval = false;
	if (m_FocusList.Num() == 0) return false; // ‘¶İ‚µ‚È‚¢

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
		romovewidget->RemoveFromParent(); // ‚±‚±‚Å‚â‚é

	}
	return retval;
}

void UFocusLogWidget::RemoveIdMin()
{
	if (index == 0 || m_FocusList.Num() == 0) return; // ‘¶İ‚µ‚È‚¢

	// ŒÃ‚¢‚à‚Ì‚ğíœ‚·‚é
	// ˆê”ÔID‚ª¬‚³‚¢‚à‚Ì
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
