// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LoopoolGameInstanceC.generated.h"


/**
 * 
 */
UCLASS()
class LOOPOOLGAME_API ULoopoolGameInstanceC : public UGameInstance
{
	GENERATED_BODY()
public:

	static ULoopoolGameInstanceC* GetInstance();


	//•Ï”

	//’e‚ğ‘Å‚Á‚½‚Æ‚«‚Ì‹­‚³
	float _shotImpluse;

	//’e‚ğŒ‚‚Á‚½‚©‚Ç‚¤‚©
	bool _shot;

	
};
