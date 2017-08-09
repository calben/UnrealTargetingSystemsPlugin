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

/// <summary>
/// A component for controlling an object with force-like controls.
/// </summary>
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
		/// <summary>
		/// TODO
		/// </summary>
		bool bIsManipulating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// TODO
		/// </summary>
		bool bMoveTargetAboutManipulatorRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// If true, increases the linear and angular damping
		/// on the target when it is grabbed.
		/// </summary>
		bool bIncreaseDampingOnCurrentTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// If true, applies a deadzone to the relative manipulator.
		/// </summary>
		bool bUseDeadzone = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// If true, applies a clamp to the distance multiplier.
		/// </summary>
		bool bEnforceMaximumForceMultiplierDistance = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// Linear damping added to target when grabbed and removed when released.
		/// </summary>
		float LinearDampingAmount = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// Angular damping added to target when grabbed and removed when released.
		/// </summary>
		float AngularDampingAmount = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// The base impulse scale multiplied with all impulses applied.
		/// </summary>
		float BaseImpulseScale = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// The base force scale multiplied with all forces applied.
		/// </summary>
		float BaseForceScale = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// If enforced with #bEnforceMaxiumForceMultiplierDistance,
		/// defines the maximum force size to be applied to a target.
		/// </summary>
		float MaximumForceMultiplierDistance = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// If enforced with #bUseDeadzone, deadzone similar to a gamepad's joystick deadzones
		/// for remote manipulating by relative position.
		/// </summary>
		float DeadzoneSize = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		/// <summary>
		/// Target to be remotely manipulated.
		/// </summary>
		class AActor* CurrentTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		/// <summary>
		/// A direct reference to the primitive component of the target.
		/// </summary>
		class UPrimitiveComponent* CurrentTargetPrimitiveRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		/// <summary>
		/// If not null, this class is used to spawn the indicator actor.
		/// </summary>
		class TSubclassOf<AActor> RelativePositionManipulatorIndicatorActorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		/// <summary>
		/// An actor to indicate the origin for the remote manipulator.
		/// </summary>
		AActor* RelativePositionManipulatorIndicatorActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		/// <summary>
		/// The location (or origin) of the relative position manipulator.
		/// </summary>
		/// This is the location from which a delta is calculated
		/// to apply forces and impulses to a target.
		/// Note that the delta calculated is not necessarily linearly applied.
		FVector RelativePositionManipulatorLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		/// <summary>
		/// The boolean that tracks whether the target is being manipulated.
		/// </summary>
		bool bIsManipulatingByRelativePosition = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// If true, sets custom render depth to true for the current target
		/// and sets render depth to false when a new item is targeted.
		/// <summary>
		bool bShouldSetCustomRenderDepthTrueForTarget = true;

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Calculates a vector direction for a 
		/// </summary>
		/// <returns></returns>
		FVector CalculateForceVectorByRestrictedRelativePosition();

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Jerks the target along the forward vector of the instantiated component.
		/// </summary>
		/// <param name="ForceScale">The multiplier for the unit vector applied as the jerk.</param>
		void AddImpulseToTargetAlongForwardVector(float ImpulseAmount);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Jerks the target towards a world point, such as a marker.
		/// </summary>
		/// <param name="Location">The world location towards which to jerk.</param>
		/// <param name="ForceScale">The multiplier for the unit vector applied as the jerk.</param>
		void AddImpulseToTargetTowardWorldLocation(FVector Location, float ImpulseAmount);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Accelerates the target along the forward vector of the instantiated component.
		/// </summary>
		/// <param name="ForceScale">The multiplier for the unit vector applied as the push.</param>
		void AddForceToTargetAlongForwardVector(float ForceScale);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Accelerates the target towards a world point, such as a marker.
		/// </summary>
		/// <param name="Location">The world location towards which to push.</param>
		/// <param name="ForceScale">The multiplier for the unit vector applied as the push.</param>
		void AddForceToTargetTowardWorldLocation(FVector Location, float ForceScale);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Enables or disables gravity on the target.
		/// </summary>
		void ToggleCurrentTargetGravity();

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Dampens velocity on target or zeroes them if dampening amount 
		/// is greater than velocity.
		/// </summary>
		/// Applies an impulse opposite the velocity direction to reduce speed.
		/// <param name="DampeningAmount">The multiplier for the unit vector applied as dampening.</param>
		void DampenTargetForces(float DampeningAmount);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Starts manipulating using the relative position controller.
		/// </summary>
		/// The relative position controller is most intuitive in VR,
		/// but it can be used in any mode.  A point in space is designated
		/// to be the origin of the manipulation.  The delta between the
		/// manipulator and origin is applied to the object as a force.
		void StartManipulatingByRelativePosition();

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Stops manipulating using the relative position controller.
		/// </summary>
		/// The relative position controller is most intuitive in VR,
		/// but it can be used in any mode.  A point in space is designated
		/// to be the origin of the manipulation.  The delta between the
		/// manipulator and origin is applied to the object as a force.
		void StopManipulatingByRelativePosition();

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Sets a new manipulated actor and releases the old manipulated object.
		/// </summary>
		/// <param name="NewTarget">The new actor to manipulate.</param>
		void SetCurrentTarget(class AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category = Manipulating)
		/// <summary>
		/// Applies a random jerking force to the current target, giving a
		/// "jump to attention" effect.
		/// </summary>
		/// <param name="ImpulseMultiplier">The impulse multiplier of the jerk, multiplied to a unit vector.</param>
		/// <param name="TorqueMultiplier">The torque multiplier of the jerk, multiplied to a unit vector.</param>
		void JerkCurrentTarget(float ImpulseMultiplier, float TorqueMultiplier);
};
