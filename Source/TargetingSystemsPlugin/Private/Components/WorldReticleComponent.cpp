// Fill out your copyright notice in the Description page of Project Settings.

#include "Private/TargetingSystemsPlugin.h"
#include "Kismet/KismetMathLibrary.h"
#include "WorldReticleComponent.h"


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

	// ...
}

void UWorldReticleComponent::UpdateReticlePositions()
{
	for (auto i = 0; i < ReticleActors.Num(); i++)
	{
		ReticleActors[i]->SetActorLocation(GetComponentLocation() + GetPositionAtAngle(ReticleAngles[i]));
		ReticleActors[i]->SetActorRotation(FRotationMatrix::MakeFromX(GetComponentLocation() - ReticleActors[i]->GetActorLocation()).Rotator());
	}
}

FVector UWorldReticleComponent::GetPositionAtAngle(float Angle)
{
	auto X = ReticleDistanceFromCenter * FMath::Cos(Angle * 0.0174533f);
	auto Y = ReticleDistanceFromCenter * FMath::Sin(Angle * 0.0174533f);
	return FVector(0.f, X, Y);
}
