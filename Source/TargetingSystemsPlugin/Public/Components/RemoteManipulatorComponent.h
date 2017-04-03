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
#include "RemoteManipulatorComponent.generated.h"

/// @cond
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
/// @endcond
class TARGETINGSYSTEMSPLUGIN_API URemoteManipulatorComponent : public USceneComponent
{

	/// @cond
	GENERATED_BODY()
	/// @endcond

public:
	// Sets default values for this component's properties
	URemoteManipulatorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsManipulating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMovedTargetAboutManipulatorRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIncreaseDampingOnCurrentTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseDeadzone = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnforceMaximumForceMultiplierDistance = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LinearDampingAmount = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AngularDampingAmount = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseImpulseScale = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseForceScale = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaximumForceMultiplierDistance = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DeadzoneSize = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AActor* CurrentTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPrimitiveComponent* CurrentTargetPrimitiveRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class TSubclassOf<AActor> RelativePositionManipulatorIndicatorActorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* RelativePositionManipulatorIndicatorActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector RelativePositionManipulatorVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsManipulatingByRelativePosition = false;

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	FVector CalculateForceVectorByRestrictedRelativePosition();

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void AddImpulseToTargetAlongForwardVector(float ImpulseAmount);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void AddImpulseToTargetTowardWorldLocation(FVector Location, float ImpulseAmount);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void AddForceToTargetAlongForwardVector(float ForceScale);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void AddForceToTargetTowardWorldLocation(FVector Location, float ForceScale);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void ToggleCurrentTargetGravity();

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void DampenTargetForces(float DampeningAmount);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void StartManipulatingByRelativePosition();

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void StopManipulatingByRelativePosition();

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void SetCurrentTarget(class AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
	void JerkCurrentTarget(float ImpulseMultiplier, float TorqueMultiplier);
};
