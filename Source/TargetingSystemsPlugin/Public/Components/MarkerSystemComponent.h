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
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/// @endcond
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
		bool bMultipleMarkerMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class TSubclassOf<class AActor> MarkerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class AActor*> DeployedMarkers;

	UFUNCTION(BlueprintCallable, Category = Markers)
		void DeployMarker(FVector WorldLocation, FRotator WorldRotation);

};