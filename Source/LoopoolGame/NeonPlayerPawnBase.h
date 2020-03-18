// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/TextRenderComponent.h"
#include "Sound/SoundBase.h"
#include "Components/TimelineComponent.h"
#include "PoolGameModeBase.h"


#include "NeonPlayerPawnBase.generated.h"


UCLASS()
class LOOPOOLGAME_API ANeonPlayerPawnBase : public APawn
{
	GENERATED_BODY()

	class UTimelineComponent *MyTimeline;

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

	//ヒットイベント
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;


public:

	//コンストラクションスクリプトで行っていた処理
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void Init();

	//あたり判定
	
	//UFUNCTION()
	//void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//スティックを回転させるメソッド
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void AxisTurnRate(float AxisValue);

	//打つ強さを決めるメソッド
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void AxisPowerRate(float AxisValue);

	//カスタムイベントで作成していたメソッド
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void ActivePawn();
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void NonActive();
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void Shot();
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void DrawLine();
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void BLInit();
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void ShowBallNum();

	//タイムライン更新時のメソッド
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void TimelineUpdateCallback(float MoveX);

	//タイムライン更新時のメソッド
	UFUNCTION(BlueprintCallable, Category = NeonPalayerPawn)
	void TimelineFinishCallback();

	//タイムラインデリゲート
	FOnTimelineFloat TimeLineUpdate{};
	FOnTimelineEvent TimeLineFinish{};







//変数
private:
	const FName BallTagName = FName(TEXT("Ball"));
	const FName StickTagName = FName(TEXT("Stick"));

	//flipflop用のboolean
	bool _ShowBallNumFlip = true;
	
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
	USoundBase *_BallShotSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	UMaterialInterface *_NeonMatEmissive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeonPlayerPawnBase")
	UMaterialInterface *_NeonMatGlass;
	


	//FTimeline  *_ShotTimeline;

	UCurveFloat *_MoveXCurve;
	UCurveFloat *_TimeCurve;





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
