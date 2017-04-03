// MIT License
// 
// Copyright(c) 2017 Calem Bendell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "TargetingSystemsPluginPrivatePCH.h"
#include "MeshTargetingSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UMeshTargetingSystemComponent::UMeshTargetingSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetEnableGravity(false);
	StaticMesh->SetCollisionProfileName(FName("OverlapAll"));
	StaticMesh->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	// ...
}


// Called when the game starts
void UMeshTargetingSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

}


// Called every frame
void UMeshTargetingSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMeshTargetingSystemComponent::SetCurrentTarget()
{
	TArray<AActor*> Overlapping;
	StaticMesh->GetOverlappingActors(Overlapping, nullptr);
	CurrentTarget = nullptr;
	float distance = 999999.f;
	for (AActor* actor : Overlapping)
	{
		if (!actor->GetName().Contains("BP_MotionController"))
		{
			float d = UKismetMathLibrary::GetPointDistanceToSegment(actor->GetActorLocation(), GetComponentLocation(), GetComponentLocation() + GetForwardVector() * 99999.f);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OBJECT %s IS %f AWAY FROM CENTER LINE"), *actor->GetName(), d));
			if (d < distance)
			{
				distance = d;
				CurrentTarget = actor;
			}
		}
	}
}


