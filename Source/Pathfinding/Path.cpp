// Fill out your copyright notice in the Description page of Project Settings.


#include "Path.h"

// Sets default values for this component's properties
UPath::UPath()
{
	// We don't need the tick function for this actor component
	PrimaryComponentTick.bCanEverTick = false;
}


// Initializes default values
void UPath::BeginPlay()
{
	Super::BeginPlay();

	TotalOpenNodes = 0;
	ExploredNodes = 0;
	HeuristicMultiplier = 100;
}


// Called every frame
void UPath::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

//Calculates the algorithm
void UPath::Solution() {
	while (OpenNodes.Num() != 0) {
		OpenNodes.StableSort([](const AGridNode& node1, const AGridNode& node2) {
			return node2 > node1;
			});
		CurrentNode = OpenNodes.Pop();
		if (CurrentNode == GoalNode) break; //WE FOUND THE SOLUTION
		TArray<AGridNode*> ChildNodes = Grid->GetValidNeighbors(CurrentNode);
		for (auto& ChildNode : ChildNodes) {
			int currentcost = CurrentNode->cost + CostNodes(CurrentNode, ChildNode);
			if (OpenNodes.Contains(ChildNode)) {
				if (ChildNode->cost <= currentcost) continue;
			}
			else if (ClosedNodes.Contains(ChildNode)) {
				if (ChildNode->cost <= currentcost) continue;
				ClosedNodes.Remove(ChildNode);
				OpenNodes.Add(ChildNode);
				TotalOpenNodes++;
				SetOpenNode(ChildNode);
			}
			else {
				OpenNodes.Add(ChildNode);
				SetOpenNode(ChildNode);
				TotalOpenNodes++;
				ChildNode->heuristic = Heuristic(ChildNode); //ADD HEURISTIC HERE, usually distance to goal
			}
			ChildNode->cost = currentcost;
			ChildNode->parent = CurrentNode;
		}
		ClosedNodes.Add(CurrentNode);
		ExploredNodes++;
		SetClosedNode(CurrentNode);
	}
}

//Shows the path obtained after the algorithm is performed
void UPath::ShowSolution() {
	if (CurrentNode == nullptr || CurrentNode != GoalNode) return;
	while (CurrentNode != StartNode) {
		CurrentNode->SetPathNode();
		CurrentNode = CurrentNode->parent;
	}
}

//Calculates the cost between two nodes
int UPath::CostNodes(AGridNode* n1, AGridNode* n2) {
	if (n1->x == n2->x || n1->y == n2->y) return 100;
	else return 142;
}

//Calculates the heuristic value of a given node based on the Euclidean distance
int UPath::Heuristic(AGridNode* n) {
	return roundf((FVector2D(n->x, n->y) - FVector2D(GoalNode->x, GoalNode->y)).Size()* HeuristicMultiplier);

}

//Sets a node as a starting node, initializing default values, cleaning the grid
//It also removes the previous starting node if existed and adds the new one to the Open Nodes list
//It also calls the function that sets the correct start node material for visual feedback
void UPath::SetStartNode(AGridNode* n) {
	if (StartNode != nullptr) StartNode->RemoveStartNode();
	if (!n->Valid()) return;
	OpenNodes.Empty();
	ClosedNodes.Empty();
	OpenNodes.Add(n);
	StartNode = n;
	Grid->Clean();
	TotalOpenNodes = 0;
	ExploredNodes = 0;
	n->SetStartNode();
}

//Sets a node as the goal node, initializing default values and cleaning the grid
//It also removes the previous goal node if existed and makes sure if a start node exists, it puts it in the open list
//It also calls the function that sets the correct goal node material for visual feedback
void UPath::SetGoalNode(AGridNode* n) {
	if (GoalNode != nullptr) GoalNode->RemoveGoalNode();
	if (!n->Valid()) return;
	GoalNode = n;
	OpenNodes.Empty();
	if (StartNode != nullptr) OpenNodes.Add(StartNode);
	ClosedNodes.Empty();
	TotalOpenNodes = 0;
	ExploredNodes = 0;
	Grid->Clean();
	n->SetGoalNode();
}

//Responsible for setting the correct open node material for visual feedback
void UPath::SetOpenNode(AGridNode* n) {
	n->SetOpenNode();
}

//Responsible for setting the correct closed node material for visual feedback
void UPath::SetClosedNode(AGridNode* n) {
	n->SetClosedNode();
}