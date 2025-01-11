// Fill out your copyright notice in the Description page of Project Settings.


#include "ATileGameManager.h"
#include "ATilePlayerController.h"

// Sets default values
AATileGameManager::AATileGameManager() :
	GridSize(100),
	GridOffSet(0,0,0.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	GridSelection = CreateDefaultSubobject<UStaticMeshComponent>("GridMesh");
	GridSelection->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		PlaneMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	/*static ConstructorHelpers::FObjectFinder<UMaterialInstance>
		GridMaterial(TEXT(""));*/

	GridSelection->SetStaticMesh(PlaneMesh.Object);
	GridSelection->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

// Called when the game starts or when spawned
void AATileGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController = Cast<AATilePlayerController>(GWorld->GetFirstPlayerController()))
	{
		PlayerController->GameManager = this;
	}
	
}

// Called every frame
void AATileGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AATileGameManager::OnActorInteractıon(AActor* Actor, FVector& Location, bool IsPressed)
{
		
	if (TileTypes.Num() == 0)return;


	FVector GridLoc = GridOffSet;
	GridLoc.X += FMath::GridSnap(Location.X, GridSize);
	GridLoc.Y += FMath::GridSnap(Location.Y, GridSize);
	GridLoc.Z += Location.Z;

	FRotator GridRot = GridOffRot;

	AATileBase* SelectedTile = TileTypes[CurrentTileIndex];
	UStaticMesh* TileMesh = SelectedTile->BaseMesh;

	UPlayerInput* Input = GWorld->GetFirstPlayerController()->PlayerInput;

	if (Input->WasJustPressed(EKeys::LeftMouseButton))
	{
		int GridX = GridLoc.X / GridSize + MapExtendsInGrid;
		int GridY = GridLoc.Y / GridSize + MapExtendsInGrid;

		if (GridX < 0 || GridY < 0 || GridX >= MapExtendsInGrid*2 || GridY >= MapExtendsInGrid*2)
		{
			return;
		}
		
		if (Map[GridX][GridY] != nullptr) return;

		if (TileTypes.IsValidIndex(CurrentTileIndex))
		{
			
			Map[GridX][GridY] = SelectedTile;

			FTransform TileTransform(GridOffRot,GridLoc + GridOffSet);
			SelectedTile->InstancedMesh->AddInstance(
				SelectedTile->InstancedMesh->GetRelativeTransform() * TileTransform, true);
			
		}

		UE_LOG(LogTemp, Warning, TEXT("Hit: %s - %f, %f,%f"),
			Actor ? *Actor->GetActorLabel() : TEXT("None"),
			Location.X,
			Location.Y,
			Location.Z);

	}
	else if (Input->WasJustPressed(EKeys::RightMouseButton))
	{
		GridRot.Pitch = GridOffRot.Pitch;
		GridRot.Roll = GridOffRot.Roll;
		GridRot.Yaw += 90;
		GridSelection->SetWorldRotation(GridRot);
		GridOffRot = GridRot;
		UE_LOG(LogTemp, Warning, TEXT("%f"),GridRot.Yaw);
	}
	else if (Input->WasJustPressed(EKeys::MouseScrollDown))
	{
		CurrentTileIndex = (CurrentTileIndex + 1) % TileTypes.Num();
		UE_LOG(LogTemp, Warning, TEXT("TileTypes = %s"), *TileTypes[CurrentTileIndex]->GetActorLabel());

	}
	else if (Input->WasJustPressed(EKeys::MouseScrollUp))
	{

			CurrentTileIndex = (CurrentTileIndex - 1) % TileTypes.Num() * -1;
			UE_LOG(LogTemp, Warning, TEXT("TileTypes = %s"), *TileTypes[CurrentTileIndex]->GetActorLabel());
	}
	else
	{
		GridSelection->SetWorldLocation(GridLoc + GridOffSet);
		GridSelection->SetStaticMesh(TileMesh);

		FVector TileRefScale(0.1f, 0.1f, 0.1f);
		GridSelection->SetRelativeScale3D(TileRefScale);

	}


	


}

