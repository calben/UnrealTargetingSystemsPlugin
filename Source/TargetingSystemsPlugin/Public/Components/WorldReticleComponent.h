// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"

#include "WorldReticleComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TARGETINGSYSTEMSPLUGIN_API UWorldReticleComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UWorldReticleComponent();

    // Called when the game starts
    virtual void BeginPlay() override;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// Class used as reticle ticks.
    /// </summary>
    TSubclassOf<AActor> ReticleActorClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    /// <summary>
    /// A collection of the actors spawned and managed by the reticle actor.
    /// </summary>
    /// A user may add to this list of reticle actors, but should you do so,
    /// make sure you also modify the list of reticle angles or your added
    /// reticle will not be added in a correct location.
    TArray<AActor*> ReticleActors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// Used to calculated reticle angles if no angles supplied.
    /// </summary>
    int DefaultNumberOfReticles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// The radius for the arrangement of reticles.
    /// </summary>
    float ReticleDistanceFromCenter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// If true, the relative locations of the reticle actors are
    /// updated every tick.
    /// </summary>
    bool bUpdateReticlePositionsOnTick;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// If set, determines the angles at which the reticles are set, ignoring
    /// number of reticles.
    /// </summary>
    TArray<float> ReticleAngles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// If reticle angles are autocalculated, added to all calculated angles.
    /// </summary>
    float ReticleAnglesOffset;

    UFUNCTION(BlueprintCallable, Category = "Reticle")
    /// <summary>
    /// Updates the positions of all reticle actors.
    /// </summary>
    void UpdateReticlePositions();

    /// <summary>
    /// Gets the (0.f, X, Y) positions as if on a 2D plane for a reticle.
    /// </summary>
    /// <param name="Angle">Angle for which to generate the (0.f, X, Y) position.</param>
    /// <returns>FVector position</returns>
    FVector GetPositionAtAngle(float Angle);
};
