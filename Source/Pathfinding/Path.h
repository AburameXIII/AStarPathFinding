// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grid.h"
#include "Path.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PATHFINDING_API UPath : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPath();

	//Reference to the grid where the algorithm will perform
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGrid* Grid;

	//List of Open Nodes
	UPROPERTY(VisibleAnywhere)
	TArray<AGridNode*> OpenNodes;

	//List of Closed/Explored Nodes
	UPROPERTY(VisibleAnywhere)
	TArray<AGridNode*> ClosedNodes;

	//Reference to the starting node
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGridNode* StartNode;

	//Reference to the goal node
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGridNode* GoalNode;

	//Amount of total different nodes added to the open nodes list
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalOpenNodes;

	//Total amount of different nodes added to the closed nodes list
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ExploredNodes;

	//Heuristic multiplier for the Euclidean Distance
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HeuristicMultiplier;

protected:
	virtual void BeginPlay() override;

	//Calculates the cost between two given nodes
	int CostNodes(AGridNode* n1, AGridNode* n2);

	//Calculates the Euclidean distance based on an heuristic multiplier
	int Heuristic(AGridNode* n);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Performs the pathfinding algorithm
	UFUNCTION(BlueprintCallable, Category = "Path Functions")
	void Solution();


	//User Interface Functions
	UFUNCTION(BlueprintCallable, Category = "Path Functions")
	void SetStartNode(AGridNode* n);

	UFUNCTION(BlueprintCallable, Category = "Path Functions")
	void SetGoalNode(AGridNode* n);

	void SetOpenNode(AGridNode* n);

	void SetClosedNode(AGridNode* n);
	
	UFUNCTION(BlueprintCallable, Category = "Path Functions")
	void ShowSolution();
		
private:

	//Keeps the current explored node as a private variable to use later when calculating the both based on the current node's parent node
	AGridNode* CurrentNode;

};
