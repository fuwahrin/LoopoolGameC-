// Fill out your copyright notice in the Description page of Project Settings.


#include "LoopoolGameInstanceC.h"
#include "Engine/Engine.h"

ULoopoolGameInstanceC* ULoopoolGameInstanceC::GetInstance()
{
	ULoopoolGameInstanceC *instance = nullptr;

	if (GEngine)
	{
		FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
		instance = Cast<ULoopoolGameInstanceC>(context->OwningGameInstance);
	}

	return instance;
}