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

#pragma once

#include "GameFramework/Actor.h"

#include "WorldSpaceReticle.generated.h"

/// @cond
UCLASS()
/// @endcond

/// <summary>
/// An actor that spawns and maintains reticle ticks in world space.
/// </summary>
/// This is designed primarily for applications that necessitate objects
/// in world space, such as VR games.
class TARGETINGSYSTEMSPLUGIN_API AWorldSpaceReticle : public AActor
{
    /// @cond
    GENERATED_BODY()
    /// @endcond

public:
    // Sets default values for this actor's properties
    AWorldSpaceReticle();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /// <summary>
    /// Scene root.
    /// </summary>
    USceneComponent* Scene;

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
