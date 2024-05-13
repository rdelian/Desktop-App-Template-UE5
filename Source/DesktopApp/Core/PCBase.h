// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCBase.generated.h"

/**
 * 
 */
UCLASS()
class DESKTOPAPP_API APCBase : public APlayerController {
	GENERATED_BODY()

	APCBase();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnWindowFocusChanged(bool bIsActive);

	UPROPERTY()
	TObjectPtr<UUserWidget> MainWidgetInstance;

public:
	/** MAX FPS While using the app (only in Production builds) */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "5", UIMax = "1000", ClampMin = "5", ClampMax = "9999"))
	int32 ActiveFrameRate;

	/** MIN FPS While the app is not in focus (only in Production builds) */
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "1", UIMax = "1000", ClampMin = "1", ClampMax = "9999"))
	int32 NotInFocusFrameRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainWidgetClass;
};
