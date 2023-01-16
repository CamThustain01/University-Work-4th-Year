// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWeapon.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AREnemyCharacter.h"

// Sets default values
AGameWeapon::AGameWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Bullet Collision"));
	CollisionSphere->InitSphereRadius(20.0f);
	
	//set up the bullet mesh, give it material, mesh, scale it
	RootComponent = CollisionSphere;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(CollisionSphere);
	auto BulletAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	BulletMat = ConstructorHelpers::FObjectFinder<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Assets/Materials/Bullet_Inst.Bullet_Inst'")).Object;
	BulletMesh->SetMaterial(0,BulletMat);
	BulletMesh->SetStaticMesh(BulletAsset.Object);
	BulletMesh->SetWorldScale3D(FVector(0.05,	0.05,0.05));

	//setup movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Movement"));
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	
	//give bullet physics, speed never increases just stays the same. 
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	//time until bullet dies if nothing is hit
	InitialLifeSpan = 2.5f;
	
	
	
}

// Called when the game starts or when spawned
void AGameWeapon::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,&AGameWeapon::onhit);
}

// Called every frame
void AGameWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//prints weapon damage, for debugging
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Weapon Damage: %d"), WeaponDamage));

}

void AGameWeapon::onhit(UPrimitiveComponent* HitComp, AActor* actor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

	AAREnemyCharacter* Enemy = Cast<AAREnemyCharacter>(actor); //casts enemy object to the actor thats hit

	if(Enemy)//checks if the thing the bullet is hitting is an enemy...
	{

		Enemy->DamageReceived(WeaponDamage); //deals damage to enenmy

		Destroy(); // destroys bullet if enemy hit

	}

		
}

