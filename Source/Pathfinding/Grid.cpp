// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

// Sets default values
AGrid::AGrid()
{
 	//The tick function is not necessary for this actor
	PrimaryActorTick.bCanEverTick = false;
}

// Initializes the grid given a certain width and height
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {
			FVector Location = FVector(100.f * x, 100.f * y, 0.f);

			AGridNode* NewNode = GetWorld()->SpawnActor<AGridNode>(AGridNode::StaticClass(), Location, FRotator::ZeroRotator);
			NewNode->x = x;
			NewNode->y = y;

			GridNodes.Add(NewNode);
		}
	}
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns a node based on given coordinates
AGridNode* AGrid::GetNode(int x, int y)
{
	return GridNodes[y * Height + x];
}

//Returns all valid neighbors of a given node
TArray<AGridNode*> AGrid::GetValidNeighbors(AGridNode* Node) {
	TArray<AGridNode*> Neighbors;

	for (int x = Node->x - 1; x <= Node->x + 1; x++) {
		for (int y = Node->y - 1; y <= Node->y + 1; y++) {
			if (x == Node->x && y == Node->y) continue;
			if (Valid(x, y)) {
				Neighbors.Add(GridNodes[y * Height + x]);
			}
		}
	}

	return Neighbors;
}

//Checks if given coordinates correspond to a valid node in the grid
bool AGrid::Valid(int x, int y) {
	if (x >= 0 && y >= 0 && x < Width && y < Height) {
		return GridNodes[y * Height + x]->Valid();
	}
	return false;
}

//Clears the nodes
void AGrid::Clean() {
	for (auto Node : GridNodes) {
		Node->Clear();
	}
}