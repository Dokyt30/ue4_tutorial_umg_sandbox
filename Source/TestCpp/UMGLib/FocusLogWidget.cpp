// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusLogWidget.h"

void UFocusLogWidget::CreateItemLogMessage()
{
	if (VerticalBoxItem == nullptr) return;


	UWidget* tmpwidget = nullptr;


	//CreateWidget<UFocusLogWidgetItem>()

	VerticalBoxItem->AddChildToVerticalBox(tmpwidget);
}