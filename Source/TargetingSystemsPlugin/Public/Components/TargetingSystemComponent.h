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

#include "Components/SceneComponent.h"

#include "TargetingSystemComponent.generated.h"

/// @cond
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
/// @endcond

/// <summary>
/// A component that adds targeting functionality to a given actor.
/// </summary>
/// This is the primary component of TargetingSystemsPlugin (aptly named, eh?).
/// Add this to an actor and set #bEnableTargeting to true and this component will
/// update the #CurrentTarget actor every tick.  This component uses a simple trace
/// to select its current target, but components extending this may use fuzzier
/// and more sophisticated methods.
class TARGETINGSYSTEMSPLUGIN_API UTargetingSystemComponent : public USceneComponent
{
    /// @cond
    GENERATED_BODY()
    /// @endcond

public:
    // Sets default values for this component's properties
    UTargetingSystemComponent();

    // Called when the game starts
    virtual void BeginPlay() override;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// If true, the component will retarget on TickComponent.
    /// </summary>
    bool bIsTargeting = true;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    /// <summary>
    /// If not null, the targeted actor.
    /// </summary>
    /// <warning>
    /// Make sure to perform a null check if accessing this value.
    /// </warning>
    class AActor* CurrentTarget;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    /// <summary>
    /// If not null, the active targets.
    /// </summary>
    TArray<class AActor*> SelectedActors;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /// <summary>
    /// If not null, the actor target before the current actor.
    /// </summary>
    /// It is often useful to know the previously targeted actor,
    /// particularly if some effect is being applied to the targeted
    /// actor and you don't want to edit more functionality into
    /// #OnTargetChanged()
    class AActor* PreviousTarget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /// <summary>
    /// The distance to target by targeting trace.
    /// </summary>
    /// For the base targeting method, this is the line trace distance
    /// obtained by trace targeting.  For other targeting systems,
    /// it may be useful for this to have a different value.
    float TargetingDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// Maximum distance to ray trace or otherwise target.
    /// </summary>
    float MaximumTargetingDistance = 5000.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /// <summary>
    /// If true, indicates that the previous target's render depth
    /// was already set to true before targeting.
    /// </summary>
    bool bCurrentTargetAlreadyTrueCustomRenderDepth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSetCustomRenderDepthOnTargets = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSetStencilValueOnInitialTargeting = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// If true, draws debug lines for the targeting trace.
    /// </summary>
    bool bDrawDebug = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, int> TagToStencilBuffer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /// <summary>
    /// If not null, uses this tag to determine valid targetables.
    /// </summary>
    TArray<FName> ValidTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, float> DurationInGaze;

    UFUNCTION(BlueprintCallable, Category = Targeting)
    /// <summary>
    /// The function used to calculate a new target.
    /// </summary>
    /// This function is typically overridden in children
    /// of this component.
    virtual void SetCurrentTarget();

    UFUNCTION(BlueprintCallable, Category = Targeting)
    /// <summary>
    /// Used to trigger behaviour when the current target changes.
    /// </summary>
    /// TODO: make this implementable
    void OnTargetChanged();

    UFUNCTION(BlueprintCallable, Category = Rendering)
    /// <summary>
    /// Sets the custom render depth to false on previous target
    /// and true on current to enable highlighting effects.
    /// </summary>
    void UpdateHighlighting();

    UFUNCTION(BlueprintCallable, Category = Targeting)
    AActor* SelectCurrentTarget();

    UFUNCTION(BlueprintCallable, Category = Targeting)
    AActor* SelectOnlyCurrentTarget();

    UFUNCTION(BlueprintCallable, Category = Targeting)
    void AddActorToSelectedActors(AActor* actor);

    UFUNCTION(BlueprintCallable, Category = Targeting)
    void RemoveActorFromSelectedActors(AActor* actor);

    UFUNCTION(BlueprintCallable, Category = Targeting)
    void SetActorStencilValueByTag(AActor* actor);
};
