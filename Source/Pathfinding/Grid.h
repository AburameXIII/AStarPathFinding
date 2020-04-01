// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridNode.h"
#include "Grid.generated.h"

UCLASS()
class PATHFINDING_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

	//Array of nodes in the grid
	UPROPERTY(VisibleAnywhere)
	TArray<AGridNode*> GridNodes;

	//Width of the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(DisplayName="Width",ExposeOnSpawn=true))
	int Width;

	//Height of the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Height", ExposeOnSpawn = true))
	int Height;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Checks if the given coordinates correspond to a valid node in the grid
	bool Valid(int x, int y);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns a node based on given coordinates
	AGridNode* GetNode(int x, int y);

	//Returns all valid neighbors of a given node
	TArray<AGridNode*> GetValidNeighbors(AGridNode* Node);

	//Clears the nodes for graphical feedback
	void Clean();

};
