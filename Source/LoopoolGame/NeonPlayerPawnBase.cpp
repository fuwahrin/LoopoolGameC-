// Fill out your copyright notice in the Description page of Project Settings.


#include "NeonPlayerPawnBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "LoopoolGameInstanceC.h"

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
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> CueStick;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstanceDynamic>NeonMat;

		//サウンド
		ConstructorHelpers::FObjectFinderOptional<USoundBase> BallHitSound;
		
		
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
			, NeonMat(TEXT("MaterialInstanceConstant'/Game/PoolTable/Material/Mat_NeonProps.Mat_NeonProps"))
		{

		}
	};
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

		RootComponent = PoolBall;



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

	}

	//変数RefBallMeshsにスタティックを設定する。
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

	//サウンド変数にサウンドをセットする。
	_BallHitSound = ConstructorStatics.BallHitSound.Get();

	//マテリアル変数の初期化
	_NeonMat = ConstructorStatics.NeonMat.Get();

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

	//各コンポーネントのコリジョン設定

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


void ANeonPlayerPawnBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//
	if((OtherActor != nullptr) && (OtherComponent != nullptr))
	{
		if (OtherComponent->ComponentHasTag(StickTagName))
		{

		}
		else if(OtherComponent->ComponentHasTag(BallTagName))
		{
			_BallToHit = true;
			
			UGameplayStatics::SpawnSoundAtLocation(this, _BallHitSound, this->GetActorLocation());
		}
	}

}

void ANeonPlayerPawnBase::ActivePawn()
{
	PoolBall->CreateDynamicMaterialInstance(0, _NeonMat, "None");


}

void ANeonPlayerPawnBase::NonActive()
{

}

void ANeonPlayerPawnBase::Shot()
{

}

void ANeonPlayerPawnBase::DrawLine()
{

}

void ANeonPlayerPawnBase::BLInit()
{

}

void ANeonPlayerPawnBase::ShowBallNum()
{

}



