// Fill out your copyright notice in the Description page of Project Settings.


#include "NeonPlayerPawnBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "LoopoolGameInstanceC.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
ANeonPlayerPawnBase::ANeonPlayerPawnBase()
{
	//アセット読み込みを構造体にまとめる
	struct FConstructorStatics
	{
		//スタティックメッシュ
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PoolBall;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber1;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber2;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber3;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber4;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber5;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber6;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber7;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber8;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber9;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber10;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber11;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber12;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber13;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber14;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>PoolBallNumber15;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>CueStick;
		ConstructorHelpers::FObjectFinderOptional<USoundBase>BallHitSound;
		ConstructorHelpers::FObjectFinderOptional<USoundBase>BallShotSound;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInterface>NeonMatEmissive;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInterface>NeonMatGlass;
		ConstructorHelpers::FObjectFinderOptional<UCurveFloat>MoveXCurve;
		ConstructorHelpers::FObjectFinderOptional<UCurveFloat>TimeCurve;



		FConstructorStatics()
			: PoolBall(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_00.Mesh_NeonBall_00"))
			, PoolBallNumber1(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_1.Mesh_NeonBall_1"))
			, PoolBallNumber2(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_2.Mesh_NeonBall_2"))
			, PoolBallNumber3(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_3.Mesh_NeonBall_3"))
			, PoolBallNumber4(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_4.Mesh_NeonBall_4"))
			, PoolBallNumber5(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_5.Mesh_NeonBall_5"))
			, PoolBallNumber6(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_6.Mesh_NeonBall_6"))
			, PoolBallNumber7(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_7.Mesh_NeonBall_7"))
			, PoolBallNumber8(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_8.Mesh_NeonBall_8"))
			, PoolBallNumber9(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_9.Mesh_NeonBall_9"))
			, PoolBallNumber10(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_10.Mesh_NeonBall_10"))
			, PoolBallNumber11(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_11.Mesh_NeonBall_11"))
			, PoolBallNumber12(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_12.Mesh_NeonBall_12"))
			, PoolBallNumber13(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_13.Mesh_NeonBall_13"))
			, PoolBallNumber14(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_14.Mesh_NeonBall_14"))
			, PoolBallNumber15(TEXT("/Game/PoolTable/Mesh/Mesh_NeonBall_15.Mesh_NeonBall_15"))
			, CueStick(TEXT("/Game/PoolTable/Mesh/Mesh_Cuestick.Mesh_Cuestick"))
			, BallHitSound(TEXT("/Game/Create/Audio/billiard-ball1.billiard-ball1"))
			, BallShotSound(TEXT("/Game/Create/Audio/billiard-shot1.billiard-shot1"))
			, NeonMatEmissive(TEXT("/Game/PoolTable/Material/Mat_NeonProps.Mat_NeonProps"))
			, NeonMatGlass(TEXT("/Game/PoolTable/Material/MI_PoolBall_Glass.MI_PoolBall_Glass"))
			, MoveXCurve(TEXT("/Game/Create/BP/Curve/MoveXCurve.MoveXCurve"))
			, TimeCurve(TEXT("/Game/Create/BP/Curve/TimeCurve.TimeCurve"))
		{

		}
	};

	//タイムライン
	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));

	static FConstructorStatics ConstructorStatics;

	
	//コンポーネントの設定
	//ルートコンポーネント（球）
	PoolBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PoolBall"));
	PoolBall->SetStaticMesh(ConstructorStatics.PoolBall.Get());
	if (PoolBall != nullptr)
	{
		//タグ
		TArray<FName> _Tags;
		_Tags.Add(BallTagName);
		PoolBall->ComponentTags = _Tags;

		

		//コリジョン
		PoolBall->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
		PoolBall->SetCollisionProfileName(TEXT("PoolBall"));
		PoolBall->SetSimulatePhysics(true);
		PoolBall->SetLinearDamping(0.2f);
		PoolBall->SetAngularDamping(0.3f);
		PoolBall->bApplyImpulseOnDamage = false;
		PoolBall->SetNotifyRigidBodyCollision(true);//Simuration Generates Hit Events

		RootComponent = PoolBall;

		//Hitイベント
		//PoolBall->OnComponentHit.AddDynamic(this, &ANeonPlayerPawnBase::OnCompHit);
		//PoolBall->NotFy


	}

	//ボールとスティックを連結するSpringArm
	SpringArmStick = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmStick"));
	if (SpringArmStick != nullptr)
	{
		//Armの長さ
		SpringArmStick->TargetArmLength = 50.0f;
		//カメラとの当たり判定を切る
		SpringArmStick->bDoCollisionTest = false;
		//親コンポーネントからPitchとYawを継承しないようにする。
		SpringArmStick->bInheritPitch = false;
		SpringArmStick->bInheritYaw = false;
		//ゲーム中表示しないようにする。
		SpringArmStick->bHiddenInGame = true;
		SpringArmStick->SetupAttachment(PoolBall);
	}

	//スティック
	CueStick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CueStick"));
	CueStick->SetStaticMesh(ConstructorStatics.CueStick.Get());
	//Hitイベントを発生させる	
	if (CueStick != nullptr)
	{
		//コリジョン関連
		CueStick->SetGenerateOverlapEvents(true);
		CueStick->SetCollisionProfileName(TEXT("Custom"));
		CueStick->SetupAttachment(SpringArmStick);

		//初期角度
		FRotator Rot = FRotator(-90.0f, 0.0f, 0.0f);
		CueStick->SetRelativeRotation(FQuat(Rot));
		CueStick->SetRelativeScale3D(FVector(1.0f, 0.5f, 0.5f));

		//タグ
		TArray<FName> _Tags;
		_Tags.Add(StickTagName);

		//コリジョン
		CueStick->SetNotifyRigidBodyCollision(true);//Simuration Generates Hit Events
		CueStick->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
		CueStick->SetCollisionProfileName(TEXT("CueStick"));

		CueStick->ComponentTags = _Tags;

	}


	//Arrowコンポーネント
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(SpringArmStick);
	if (Arrow != nullptr)
	{
		Arrow->bHiddenInGame = false;
		Arrow->ArrowColor.Red;
		Arrow->ArrowSize = 0.2f;

		//初期位置
		Arrow->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
	}

	//ボールとTextを連結するArmSpring
	SpringArmText = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmText"));
	SpringArmText->SetupAttachment(PoolBall);
	if (SpringArmText != nullptr)
	{
		SpringArmText->TargetArmLength = 1.5f;
		SpringArmText->bDoCollisionTest = false;
		SpringArmText->bInheritPitch = false;
		SpringArmText->bInheritYaw = false;
		SpringArmText->bInheritRoll = false;

		//初期角度
		FRotator Rot = FRotator(-90.0f, 0.0f, 0.0f);
		SpringArmText->SetRelativeRotation(FQuat(Rot));
	}

	//ナンバーテキスト
	NumberText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NumberText"));
	NumberText->SetupAttachment(SpringArmText);
	if (NumberText != nullptr)
	{
		NumberText->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
		NumberText->WorldSize = 100.0f;

		//初期角度
		FRotator Rot = FRotator(0.0f, -180.0f, 90.0f);
		NumberText->SetRelativeRotation(FQuat(Rot));
		//テキストを見えなくする。
		NumberText->SetVisibility(false);
		NumberText->WorldSize = 16.0f;

	}

	//変数RefBallMeshsにスタティックを設定する。
	_RefBallMeshes.Add(ConstructorStatics.PoolBall.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber1.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber2.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber3.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber4.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber5.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber6.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber7.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber8.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber9.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber10.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber11.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber12.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber13.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber14.Get());
	_RefBallMeshes.Add(ConstructorStatics.PoolBallNumber15.Get());

	//弾の半径を設定
	_BallRadius = 3.25f;
	//サウンド変数にサウンドをセットする。
	_BallHitSound = ConstructorStatics.BallHitSound.Get();
	_BallShotSound = ConstructorStatics.BallShotSound.Get();

	//マテリアル変数の初期化
	_NeonMatEmissive = ConstructorStatics.NeonMatEmissive.Get();
	_NeonMatGlass = ConstructorStatics.NeonMatGlass.Get();

	//タイムライン
	//_ShotTimeline = new FTimeline();
	//_ShotTimeline->SetTimelineLength(5.0f);

	//タイムラインで使用するカーブ
	_MoveXCurve = ConstructorStatics.MoveXCurve.Get();
	_TimeCurve = ConstructorStatics.TimeCurve.Get();

	//タイムライン更新時呼ばれる関数の設定（このクラスのTimelineUpdate）を呼ぶ
	//FOnTimelineFloat MyTimelineUpdate;
	//MyTimelineUpdate.BindUFunction(this, "TimelineUpdate");
	TimeLineUpdate.BindUFunction(this, FName("TimelineUpdateCallBack"));
	TimeLineFinish.BindUFunction(this, FName("TimelineFinishCallBack"));


	//打つときの強さ関連の変数の初期化
	//TODO:Input関連の処理を理解したらPlayerControllerに移動すること
	_ImpluseValue = 100.0f;
	_ImpluseMaxValue = 5.0f;
	_ImpluseMinValue = 1.0f;
	_ImpluseDefaultValue = 3.0f;

}

// Called when the game starts or when spawned
void ANeonPlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();

	Init();

}

//コンストラクションスクリプトの処理をまとめたメソッド
void ANeonPlayerPawnBase::Init()
{
	//メッシュの設定
	PoolBall->SetStaticMesh(_RefBallMeshes[_BallNumber]);

	//マテリアルインスタンスの変更
	PoolBall->CreateDynamicMaterialInstance(0, _NeonMatEmissive);
	//エミッシブカラーを強くして発光させる
	PoolBall->SetScalarParameterValueOnMaterials("Emissive_Multiply", 10.0f);

	//マテリアルインスタンスの変更
	PoolBall->CreateDynamicMaterialInstance(1, _NeonMatGlass);

	//ガラス部分を半透明にする/
	PoolBall->SetScalarParameterValueOnMaterials("Opacity", 0.5f);

	//テキストの設定
	NumberText->SetText(UKismetStringLibrary::Conv_IntToString(_BallNumber));

	//タイムラインの設定
	
	MyTimeline->AddInterpFloat(_MoveXCurve, TimeLineUpdate, FName("MoveX"));
	MyTimeline->SetTimelineFinishedFunc(TimeLineFinish);
	MyTimeline->SetLooping(false);
	MyTimeline->SetTimelineLength(1.0f);
		
}



// Called every frame
void ANeonPlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ANeonPlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//入力関連の関数

//打つ方向を決めるメソッド
void ANeonPlayerPawnBase::AxisTurnRate(float AxisValue)
{
	ULoopoolGameInstanceC *instance = Cast < ULoopoolGameInstanceC >(GetGameInstance());

	if (instance)
	{
		//まだ打っていないなら
		if (!instance->_shot && AxisValue != 0.0f)
		{
			if (IsValid(this))
			{
				//スティックの回転を設定
				SpringArmStick->AddRelativeRotation(FRotator(0.0f, 0.0f, AxisValue));

			}

		}
	}

}

//打つ強さを決めるメソッド
void ANeonPlayerPawnBase::AxisPowerRate(float AxisValue)
{
	ULoopoolGameInstanceC *instance = Cast < ULoopoolGameInstanceC >(GetGameInstance());

	if (instance)
	{
		
		//まだ打っていないなら
		if (instance->_shot)
		{
			//現在の打つ強さが最大値より低いか最小値より高いなら
			if (instance->_shotImpluse <= _ImpluseMaxValue || instance->_shotImpluse >= _ImpluseMinValue)
			{
				instance->_shotImpluse += AxisValue / 10.0f;//0.1ずつ打つ強さ（ShotImplus）を増加する。
			}
			else if(instance->_shotImpluse >= _ImpluseMaxValue)
			{
				//最大値を超えるなら、打つ強さを最大値に設定
				instance->_shotImpluse = _ImpluseMaxValue;
			}
			else if (instance->_shotImpluse <= _ImpluseMinValue)
			{
				//最小値以下なら、打つ強さを最小値に設定
				instance->_shotImpluse = _ImpluseMinValue;
			}
			
		}
	}

}

void ANeonPlayerPawnBase::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
		
	//インスタンスの取得
	ULoopoolGameInstanceC *instance = Cast < ULoopoolGameInstanceC >(GetGameInstance());

	//UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	if (instance)
	{
		if ((Other != nullptr) && (OtherComp != nullptr))
		{
			if (OtherComp->ComponentHasTag(StickTagName))
			{
				//打った強さ

				FVector shotStrongIsWindow = Hit.ImpactNormal * (instance->_shotImpluse * 25);
				
				//打った強さのベクトルの長さ
				float Length = UKismetMathLibrary::Vector4_Size(shotStrongIsWindow);
				FString LengthString = UKismetStringLibrary::Conv_FloatToString(Length);
				GLog->Log("Length =" + LengthString);
				
				//打つ際の衝撃結果を変数に格納
				_Impluse = FVector(shotStrongIsWindow.X, shotStrongIsWindow.Y, 0.0f);
				//打つ強さ確認
				GLog->Log("Inpluse =" + _Impluse.ToString());

				//ボールに衝撃を与える //最大１1
				PoolBall->AddImpulse(_Impluse);

				//ボールの衝撃音を再生
				UAudioComponent *shotAudio = UGameplayStatics::SpawnSoundAtLocation(this, _BallShotSound, this->GetActorLocation());
				float volume = UKismetMathLibrary::Vector4_Size(Hit.ImpactNormal * 1.5f);
				shotAudio->SetVolumeMultiplier(volume);

				//スティックを見えなくする。
				CueStick->SetVisibility(false, false);
				//スティックのコリジョンを消す
				CueStick->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			}
			else if (OtherComp->ComponentHasTag(BallTagName))
			{
				_BallToHit = true;
				//ボールのHit音を再生
				UAudioComponent *hitAudio = UGameplayStatics::SpawnSoundAtLocation(this, _BallHitSound, this->GetActorLocation());

				//音量を変更する。
				float volume = UKismetMathLibrary::Vector4_Size(Hit.ImpactNormal);
				hitAudio->SetVolumeMultiplier(volume);

			}
		}
	}
}

//打つボールに選択されたときに処理をまとめたメソッド
void ANeonPlayerPawnBase::ActivePawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Active"));

	//マテリアルインスタンスの変更
	PoolBall->CreateDynamicMaterialInstance(0, _NeonMatEmissive);
	//エミッシブカラーを強くして発光させる
	PoolBall->SetScalarParameterValueOnMaterials("Emissive_Multiply", 10.0f);

	//マテリアルインスタンスの変更
	PoolBall->CreateDynamicMaterialInstance(1, _NeonMatGlass);
	
	//ガラス部分を半透明にする/
	PoolBall->SetScalarParameterValueOnMaterials("Opacity", 0.5f);

	//コリジョンのチャンネルを変更（スティックのみに当たり判定を有効にするため）
	PoolBall->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	//スティックを見せる
	CueStick->SetVisibility(true, false);

	//スティックのコリジョンを有効にする。
	CueStick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//矢印を表示する。
	Arrow->SetVisibility(true, false);
}

//打つボールに選択されなかったときの処理をまとめたメソッド
void ANeonPlayerPawnBase::NonActive()
{
	ULoopoolGameInstanceC *instance = Cast < ULoopoolGameInstanceC >(GetGameInstance());

	if (instance)
	{

		UE_LOG(LogTemp, Warning, TEXT("NonActive"));
		//マテリアルインスタンスの変更
		PoolBall->CreateDynamicMaterialInstance(0, _NeonMatEmissive);
		//発光をデフォルト値に戻す。
		PoolBall->SetScalarParameterValueOnMaterials("Emissive_Multiply", 1.0f);

		//マテリアルインスタンスの変更
		PoolBall->CreateDynamicMaterialInstance(1, _NeonMatGlass);

		//ガラス部分を透明にする/
		PoolBall->SetScalarParameterValueOnMaterials("Opacity", 0.0f);
		
		//コリジョンのチャンネルを変更（スティックとのあたり判定を無効にする。）
		PoolBall->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

		//スティックを非表示
		CueStick->SetVisibility(false , false);

		//スティックのコリジョンを無効にする。
		CueStick->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//打ち終わりにスティックの位置を元に戻す。
		CueStick->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		//打つ強さを初期化
		instance->_shotImpluse = _ImpluseDefaultValue;

		//矢印を表示する。
		Arrow->SetVisibility(false, false);
	}
}

void ANeonPlayerPawnBase::Shot()
{
	//GameInstance取得
	ULoopoolGameInstanceC *instance = Cast < ULoopoolGameInstanceC >(GetGameInstance());


	UE_LOG(LogTemp, Warning, TEXT("Shot"));

	if (instance)
	{
		instance->_shot = true;

		
		if (MyTimeline != nullptr)
		{
			MyTimeline->PlayFromStart();
		}
	}

}

void ANeonPlayerPawnBase::DrawLine()
{
	//GameInstance取得
	ULoopoolGameInstanceC *instance = Cast < ULoopoolGameInstanceC >(GetGameInstance());

	if (instance)
	{
		//弾を打っているか
		if (instance->_shot)
		{
			//弾を打ったらArrowコンポーネントを非表示
			Arrow->SetVisibility(false, false);
		}
		else
		{
			//Arrowの長さを打つ強さの値によって変更する。（そのままの値では大きすぎるので2で割っている。）
			float scaleX = instance->_shotImpluse / 2.0f;
			Arrow->SetRelativeScale3D(FVector(scaleX, 1.0f, 1.0f));

			//Arrowの色を変更

			//Lerp補完のアルファ値（打つ強さを最小値と最大値の間で正規化）
			float alpha = UKismetMathLibrary::NormalizeToRange(instance->_shotImpluse, _ImpluseMinValue, _ImpluseMaxValue);

			//色を打つ強さによって変更する。
			FLinearColor color = UKismetMathLibrary::LinearColorLerp(FLinearColor::Blue, FLinearColor::Red, alpha);
			Arrow->SetArrowColor(color);

		}
	}
}

//プレイヤーのショットフラグとHitフラグを初期化
void ANeonPlayerPawnBase::BLInit()
{
	//GameInstance取得
	ULoopoolGameInstanceC *instance = Cast < ULoopoolGameInstanceC >(GetGameInstance());

	
	if (instance)
	{
		instance->_shot = false;
		_BallToHit = false;

	}
}

//ボールの番号を見せる
void ANeonPlayerPawnBase::ShowBallNum()
{
	//FlipFlop用のbool変数によって処理を分ける
	if (_ShowBallNumFlip)
	{
		NumberText->SetVisibility(true, false);
	}
	else
	{
		NumberText->SetVisibility(false, false);

	}
	//フラグを反転
	_ShowBallNumFlip = UKismetMathLibrary::Not_PreBool(_ShowBallNumFlip);

}


//タイムライン更新中に呼ばれるメソッド
void ANeonPlayerPawnBase::TimelineUpdateCallback(float MoveX)
{
	CueStick->SetRelativeLocation(FVector(MoveX , 0.0f, 0.0f));
	//GLog->Log("PLAY");
	//GLog->Log("Move =" + UKismetStringLibrary::Conv_FloatToString(MoveX));
}


//タイムライン終了時に呼ばれるメソッド
void ANeonPlayerPawnBase::TimelineFinishCallback()
{
	GLog->Log("FINISH");
}




