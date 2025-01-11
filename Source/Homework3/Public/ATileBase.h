// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "ATileBase.generated.h"

UCLASS()
class HOMEWORK3_API AATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATileBase();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMesh* BaseMesh;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* InstancedMesh;

	virtual void OnConstruction(const FTransform& Transform) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
