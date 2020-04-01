// Fill out your copyright notice in the Description page of Project Settings.


#include "GridNode.h"

// Sets default values for mesh and materials used
AGridNode::AGridNode()
{
	//we don't need to use the tick function for this actor
	PrimaryActorTick.bCanEverTick = false;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if (TileAsset.Succeeded()) {
		TileMesh->SetStaticMesh(TileAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> OpenMaterialR(TEXT("Material'/Game/OpenMaterial.OpenMaterial'"));
	OpenMaterial = OpenMaterialR.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> ClosedMaterialR(TEXT("Material'/Game/ClosedMaterial.ClosedMaterial'"));
	ClosedMaterial = ClosedMaterialR.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> StartMaterialR(TEXT("Material'/Game/StartMaterial.StartMaterial'"));
	StartMaterial = StartMaterialR.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> GoalMaterialR(TEXT("Material'/Game/GoalMaterial.GoalMaterial'"));
	GoalMaterial = GoalMaterialR.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> PathMaterialR(TEXT("Material'/Game/PathMaterial.PathMaterial'"));
	PathMaterial = PathMaterialR.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> WallMaterialR(TEXT("Material'/Game/WallMaterial.WallMaterial'"));
	WallMaterial = WallMaterialR.Object;
}

// Each node is valid at the beginning of the application
void AGridNode::BeginPlay()
{
	Super::BeginPlay();
	valid = true;
}

// Called every frame
void AGridNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Check if the node is valid for search
bool AGridNode::Valid() {
	return valid;
}

// Give the node a start node material
void AGridNode::SetStartNode() {
	OpenOrClosed = true;
	TileMesh->SetMaterial(0, StartMaterial);
}

// Give the node a goal node material
void AGridNode::SetGoalNode() {
	OpenOrClosed = true;
	TileMesh->SetMaterial(0, GoalMaterial);
}

// Remove the material from the node
void AGridNode::RemoveGoalNode() {
	OpenOrClosed = false;
	TileMesh->SetMaterial(0, nullptr);
}

// Remove the material from the node
void AGridNode::RemoveStartNode() {
	OpenOrClosed = false;
	TileMesh->SetMaterial(0, nullptr);
}

// Give the node an open node material if its not the goal or start node
void AGridNode::SetOpenNode() {
	if (!OpenOrClosed) TileMesh->SetMaterial(0, OpenMaterial);
}

// Give the node a closed node material if its not the goal or start node
void AGridNode::SetClosedNode() {
	if (!OpenOrClosed) TileMesh->SetMaterial(0, ClosedMaterial);
}

// Give the node a path material if its not the goal or start node
void AGridNode::SetPathNode() {
	if (!OpenOrClosed) TileMesh->SetMaterial(0, PathMaterial);
}

// clears the material of the node if its not an obstacle/wall or if its the start or goal node
void AGridNode::Clear() {
	if (!OpenOrClosed && valid) TileMesh->SetMaterial(0, nullptr);
}

// Creates an obstacle at this node, making it invalid for search
void AGridNode::SetWall() {
		if (!OpenOrClosed) {
			valid = false;
			TileMesh->SetMaterial(0, WallMaterial);
		}
}
