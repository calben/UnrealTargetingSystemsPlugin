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

#include "Components/TargetingSystemComponent.h"

#include "TargetingSystemsPlugin.h"

UTargetingSystemComponent::UTargetingSystemComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTargetingSystemComponent::BeginPlay()
{
    Super::BeginPlay();
}

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
        if (CurrentTarget != nullptr)
        {
            FString TargetName = CurrentTarget->GetName();
            if (DurationInGaze.Contains(TargetName))
            {
                DurationInGaze[TargetName] += DeltaTime;
            }
            else
            {
                DurationInGaze.Add(TargetName, DeltaTime);
            }
        }
    }
}

void UTargetingSystemComponent::SetCurrentTarget()
{
    CurrentTarget = nullptr;
    FHitResult            f(ForceInit);
    FVector               start     = this->GetComponentLocation();
    FVector               direction = this->GetForwardVector();
    FCollisionQueryParams params    = FCollisionQueryParams(FName(TEXT("TargetingTrace")), true, NULL);
    start                           = start + (direction * 10.0f);
    FVector end                     = start + (direction * MaximumTargetingDistance);
    GetWorld()->LineTraceSingleByChannel(f, start, end, ECC_Visibility, params);
    if (bDrawDebug)
    {
        GetWorld()->DebugDrawTraceTag = "TargetingTrace";
    }
    TargetingDistance = f.Distance;
    CurrentTarget     = f.GetActor();
}

void UTargetingSystemComponent::OnTargetChanged()
{
    if (bSetCustomRenderDepthOnTargets)
    {
        UpdateHighlighting();
    }
}

void UTargetingSystemComponent::UpdateHighlighting()
{
    // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("UPDATING HIGHLIGHTING")));
    if (PreviousTarget)
    {
        UPrimitiveComponent* preprim = Cast<UPrimitiveComponent>(PreviousTarget->GetRootComponent());
        if (preprim && !bCurrentTargetAlreadyTrueCustomRenderDepth && bSetCustomRenderDepthOnTargets &&
            !SelectedActors.Contains(PreviousTarget))
        {
            preprim->SetRenderCustomDepth(false);
        }
    }
    if (CurrentTarget)
    {
        UPrimitiveComponent* currprim = Cast<UPrimitiveComponent>(CurrentTarget->GetRootComponent());
        if (currprim)
        {
            if (currprim->bRenderCustomDepth)
            {
                bCurrentTargetAlreadyTrueCustomRenderDepth = true;
            }
            else
            {
                bCurrentTargetAlreadyTrueCustomRenderDepth = false;
                currprim->SetRenderCustomDepth(true);
                if (bSetStencilValueOnInitialTargeting)
                {
                    SetActorStencilValueByTag(CurrentTarget);
                }
            }
        }
    }
}

AActor* UTargetingSystemComponent::SelectCurrentTarget()
{
    AddActorToSelectedActors(CurrentTarget);
    return CurrentTarget;
}

AActor* UTargetingSystemComponent::SelectOnlyCurrentTarget()
{
    AddActorToSelectedActors(CurrentTarget);
    return CurrentTarget;
}

void UTargetingSystemComponent::AddActorToSelectedActors(AActor* actor)
{
    if (actor != nullptr)
    {
        this->SelectedActors.Add(actor);
        SetActorStencilValueByTag(actor);
    }
}

void UTargetingSystemComponent::RemoveActorFromSelectedActors(AActor* actor)
{
    if (actor != nullptr)
    {
        if (SelectedActors.Contains(actor))
        {
            if (bSetCustomRenderDepthOnTargets)
            {
                UPrimitiveComponent* prim = Cast<UPrimitiveComponent>(actor->GetRootComponent());
                prim->SetRenderCustomDepth(false);
            }
            SelectedActors.Remove(actor);
        }
    }
}

void UTargetingSystemComponent::SetActorStencilValueByTag(AActor* actor)
{
    if (actor != nullptr)
    {
        if (bSetCustomRenderDepthOnTargets)
        {
            UPrimitiveComponent* prim = Cast<UPrimitiveComponent>(actor->GetRootComponent());
            uint32               stencil_value;
            // actors will probably have fewer tags than the tag to buffer list
            // but if your actors have many tags it may be more performant to iterate through the tag map
            // rather than iterating through the actor tags
            for (FName name : actor->Tags)
            {
                auto name_string = name.ToString();
                if (TagToStencilBuffer.Contains(name_string))
                {
                    stencil_value = TagToStencilBuffer[name_string];
                    break;
                }
            }
            prim->SetCustomDepthStencilValue(stencil_value);
        }
    }
}
