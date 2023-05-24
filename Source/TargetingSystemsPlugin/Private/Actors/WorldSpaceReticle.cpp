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

#include "Actors/WorldSpaceReticle.h"

#include "TargetingSystemsPlugin.h"

// Sets default values
AWorldSpaceReticle::AWorldSpaceReticle()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Scene         = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    RootComponent = Scene;
}

// Called when the game starts or when spawned
void AWorldSpaceReticle::BeginPlay()
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
            AActor* Reticle = GetWorld()->SpawnActor<AActor>(
                ReticleActorClass, GetActorLocation() + GetPositionAtAngle(Angle), FRotator::ZeroRotator);
            Reticle->SetActorRotation(FRotationMatrix::MakeFromX(GetActorLocation() - Reticle->GetActorLocation()).Rotator());
            ReticleActors.Add(Reticle);
            Reticle->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        }
    }
}

// Called every frame
void AWorldSpaceReticle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWorldSpaceReticle::UpdateReticlePositions()
{
    for (auto i = 0; i < ReticleActors.Num(); i++)
    {
        ReticleActors[i]->SetActorLocation(GetActorLocation() + GetPositionAtAngle(ReticleAngles[i]));
        ReticleActors[i]->SetActorRotation(
            FRotationMatrix::MakeFromX(GetActorLocation() - ReticleActors[i]->GetActorLocation()).Rotator());
    }
}

FVector AWorldSpaceReticle::GetPositionAtAngle(float Angle)
{
    auto X = ReticleDistanceFromCenter * FMath::Cos(Angle * 0.0174533f);
    auto Y = ReticleDistanceFromCenter * FMath::Sin(Angle * 0.0174533f);
    return FVector(0.f, X, Y);
}
