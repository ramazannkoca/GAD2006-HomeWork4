// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATileBase.h"
#include "ATileGameManager.generated.h"

#define MAX_MAP_GRID_SIZE 100
 
UCLASS()
class HOMEWORK3_API AATileGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATileGameManager();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* GridSelection;

	UPROPERTY(VisibleAnywhere)

	UStaticMeshComponent* TileRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnActorInteractıon(AActor* Actor, FVector& Location, bool IsPressed);

	UPROPERTY(EditAnywhere)
	int GridSize;

	UPROPERTY(EditAnywhere)
	FVector GridOffSet;

	UPROPERTY(EditAnywhere)
	FRotator GridOffRot;

	UPROPERTY(EditAnywhere)
	TArray<AATileBase*> TileTypes;

	UPROPERTY(EditAnywhere)
	int MapExtendsInGrid;

	UPROPERTY(EditAnywhere)
	int CurrentTileIndex;

	AATileBase* Map[MAX_MAP_GRID_SIZE][MAX_MAP_GRID_SIZE];


};
