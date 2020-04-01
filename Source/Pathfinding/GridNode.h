// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridNode.generated.h"

UCLASS()
class PATHFINDING_API AGridNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridNode();

	//Mesh of the tile
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TileMesh;

	//Coordinates of the node
	int x, y;

	//Cost and Heuristic value of the current node
	int cost, heuristic;

	//Determines if the node is valid for search or not
	bool valid;

	//Compares two nodes, a node is bigger than another if the sum of its cost and heuristic value is bigger
	bool operator > (const AGridNode& pn) const { return cost + heuristic < pn.cost + pn.heuristic; }

	//Compares two nodes, they are the same if their coordinates match
	bool operator == (const AGridNode& pn) const { return x == pn.x && y == pn.y; }

	//Parent node used to calculate the path once the algorithm finishes.
	AGridNode* parent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Auxiliary functions for graphical display
	void SetStartNode();

	void SetGoalNode();

	void SetPathNode();

	void SetOpenNode();

	void SetClosedNode();

	void RemoveStartNode();

	void RemoveGoalNode();

	void Clear();

	//Sets a given node as an obstacle
	UFUNCTION(BlueprintCallable, Category = "Node Function")
	void SetWall();

	//Check is a given node is valid for search
	bool Valid();

private:

	//Auxiliary Materials
	class UMaterial* StartMaterial;
	class UMaterial* GoalMaterial;
	class UMaterial* OpenMaterial;
	class UMaterial* ClosedMaterial;
	class UMaterial* PathMaterial;
	class UMaterial* WallMaterial;
	//Auxiliary flag for graphical display
	bool OpenOrClosed = false;

};
