// Fill out your copyright notice in the Description page of Project Settings.


#include "ATileBase.h"

// Sets default values
AATileBase::AATileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	InstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("InstancedMesh");
	InstancedMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	InstancedMesh->SetStaticMesh(CubeMesh.Object);
	InstancedMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void AATileBase::OnConstruction(const FTransform& Transform)
{
	if (!BaseMesh)return;
	InstancedMesh->SetStaticMesh(BaseMesh);
}

// Called when the game starts or when spawned
void AATileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

