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
#include "MarkerSystemComponent.generated.h"

/// @cond
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
/// @endcond

/// <summary>
/// A component designed to spawn and manage markers into the world.
/// </summary>
/// The markers are intended to be used a reference points in the world.
/// For example, I might spawn a marker and then use the marker location
/// as the world location towards which the remote manipulator should 
/// push a given object.
class TARGETINGSYSTEMSPLUGIN_API UMarkerSystemComponent : public USceneComponent
{
	/// @cond
	GENERATED_BODY()
		/// @endcond

public:
	// Sets default values for this component's properties
	UMarkerSystemComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// Enables more than one marker to be placed in the world.
		/// </summary>
		bool bMultipleMarkerMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// The Class or Blueprint to use when spawning a marker in the world.
		/// </summary>
		class TSubclassOf<class AActor> MarkerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/// <summary>
		/// A list of currently deployed markers.
		/// </summary>
		TArray<class AActor*> DeployedMarkers;

	UFUNCTION(BlueprintCallable, Category = Markers)
		/// <summary>
		/// Deploys a marker at the desired world location.
		/// </summary>
		/// <param name="WorldLocation">The location at which to spawn the marker.</param>
		/// <param name="WorldRotation">The rotation with which to spawn the marker.</param>
		void DeployMarker(FVector WorldLocation, FRotator WorldRotation);

};