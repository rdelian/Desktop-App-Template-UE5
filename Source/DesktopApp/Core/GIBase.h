// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Logging/StructuredLog.h"
#include "GIBase.generated.h"

class UUserWidget;

/**
 * Create a blueprint that inherits from this class in order to set MainWidgetClass
 */
UCLASS()
class DESKTOPAPP_API UGIBase : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	/** The MAX FPS only in Production builds. */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "5", UIMax = "1000", ClampMin = "5", ClampMax = "9999"))
	int32 FrameRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UUserWidget> MainWidgetInstance;

private:
	UGIBase();

	void Init() override;

	void StartLogic(UWorld* Map);
};
