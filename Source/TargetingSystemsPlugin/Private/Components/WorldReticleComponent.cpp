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

#include "Components/WorldReticleComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "TargetingSystemsPlugin.h"

// Sets default values for this component's properties
UWorldReticleComponent::UWorldReticleComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UWorldReticleComponent::BeginPlay()
{
    Super::BeginPlay();

    if (ReticleAngles.Num())
    {
        DefaultNumberOfReticles = ReticleAngles.Num();
    }
    else
    {
        for (auto i = 0; i < DefaultNumberOfReticles; i++)
        {
            ReticleAngles.Add(ReticleAnglesOffset + (i * 360.f / DefaultNumberOfReticles));
        }
    }

    if (ReticleActorClass)
    {
        for (float Angle : ReticleAngles)
        {
            AActor* Reticle = GetWorld()->SpawnActor<AActor>(ReticleActorClass, GetComponentLocation(), FRotator::ZeroRotator);
            ReticleActors.Add(Reticle);
            Reticle->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
            Reticle->SetActorRelativeLocation(GetPositionAtAngle(Angle));
            Reticle->SetActorRelativeRotation(FRotationMatrix::MakeFromX(-GetPositionAtAngle(Angle)).Rotator());
        }
    }
}

// Called every frame
void UWorldReticleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bUpdateReticlePositionsOnTick)
    {
        UpdateReticlePositions();
    }
}
void UWorldReticleComponent::UpdateReticlePositions()
{
    for (auto i = 0; i < ReticleActors.Num(); i++)
    {
        ReticleActors[i]->SetActorRelativeLocation(GetPositionAtAngle(ReticleAngles[i]));
        ReticleActors[i]->SetActorRelativeRotation(FRotationMatrix::MakeFromX(-GetPositionAtAngle(ReticleAngles[i])).Rotator());
    }
}

FVector UWorldReticleComponent::GetPositionAtAngle(float Angle)
{
    auto X = ReticleDistanceFromCenter * FMath::Cos(Angle * 0.0174533f);
    auto Y = ReticleDistanceFromCenter * FMath::Sin(Angle * 0.0174533f);
    return FVector(0.f, X, Y);
}
