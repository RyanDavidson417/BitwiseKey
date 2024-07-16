// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BWK_UserWidget.h"
#include "BitwiseKey/BitwiseKey.h"

void UBWK_UserWidget::OnStartButtonPressed_Implementation()
{
	LOG("hiding menu")
	this->HideMenu();
}
