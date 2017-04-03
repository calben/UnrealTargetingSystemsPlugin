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
#include "TargetingSystemComponent.h"


// Sets default values for this component's properties
UTargetingSystemComponent::UTargetingSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTargetingSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTargetingSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (this->bIsTargeting)
	{
		PreviousTarget = CurrentTarget;
		SetCurrentTarget();
		if (PreviousTarget != CurrentTarget)
		{
			OnTargetChanged();
		}
	}
	// ...
}


void UTargetingSystemComponent::SetCurrentTarget()
{
	//if (CurrentTarget)
	//{
	//	UActorComponent* Light = CurrentTarget->FindComponentByClass(UPointLightComponent::StaticClass());
	//	if (Light)
	//	{
	//		Light->DestroyComponent();
	//	}
	//}
	FHitResult f(ForceInit);
	FVector start = this->GetComponentLocation();
	FVector direction = this->GetForwardVector();
	FCollisionQueryParams  params = FCollisionQueryParams(FName(TEXT("TargetingTrace")), true, NULL);
	params.bTraceAsyncScene = true;
	start = start + (direction * 10.0f);
	FVector end = start + (direction * 2000.0f);
	GetWorld()->LineTraceSingleByChannel(f, start, end, ECC_Visibility, params);
	if (bDrawDebug)
	{
		GetWorld()->DebugDrawTraceTag = "TargetingTrace";
	}
	CurrentTarget = f.GetActor();
}

void UTargetingSystemComponent::OnTargetChanged()
{
	UpdateHighlighting();
}

void UTargetingSystemComponent::UpdateHighlighting()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("UPDATING HIGHLIGHTING")));
	if (PreviousTarget)
	{
		UPrimitiveComponent* preprim = PreviousTarget->GetRootPrimitiveComponent();
		if (preprim)
		{
			preprim->SetRenderCustomDepth(false);
		}
	}
	if (CurrentTarget)
	{
		UPrimitiveComponent* currprim = CurrentTarget->GetRootPrimitiveComponent();
		if (currprim)
		{
			currprim->SetRenderCustomDepth(true);
		}
	}
}
