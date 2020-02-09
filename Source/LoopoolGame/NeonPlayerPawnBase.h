// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/TextRenderComponent.h"
#include "Sound/SoundBase.h"

#include "NeonPlayerPawnBase.generated.h"


UCLASS()
class LOOPOOLGAME_API ANeonPlayerPawnBase : public APawn
{
	GENERATED_BODY()


//コンポーネント
	UPROPERTY(Category = NeonPlayerPawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *PoolBall;

	UPROPERTY(Category = NeonPlayerPawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *SpringArmStick;

	UPROPERTY(Category = NeonPlayerPawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *CueStick;

	UPROPERTY(Category = NeonPlayerPawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent *Arrow;

	UPROPERTY(Category = NeonPlayerPawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *SpringArmText;

	UPROPERTY(Category = NeonPlayerPawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent *NumberText;


public:
	// Sets default values for this pawn's properties
	ANeonPlayerPawnBase();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//あたり判定
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//スティックを回転させるメソッド
	void AxisTurnRate(float AxisValue);

	//打つ強さを決めるメソッド
	void AxisPowerRate(float AxisValue);

	//カスタムイベントで作成していたメソッド
	void ActivePawn();

	void NonActive();

	void Shot();

	void DrawLine();

	void BLInit();

	void ShowBallNum();





//変数
private:
	const FName BallTagName = FName(TEXT("Ball"));
	const FName StickTagName = FName(TEXT("Stick"));
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	FString _PawnDisPlayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	int _PawnNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	float _BallRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	bool _BallToHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	FVector _Impluse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	TArray<UStaticMesh*> _RefBallMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	int _BallNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	USoundBase *_BallHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	UMaterialInstanceDynamic *_NeonMat;


	//PlayerControllerにもたせていた変数
	//TODO：インプット入力の受け取りがわかったらPlayerControllerに移動すること

	//打つ強さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	float _ImpluseValue;

	//打つときの最大の強さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	float _ImpluseMaxValue;

	//打つときの最小の強さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	float _ImpluseMinValue;

	//打つときのデフォルトの強さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	float _ImpluseDefaultValue;
};
