// Fill out your copyright notice in the Description page of Project Settings.


#include "PCBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Framework/Application/SlateApplication.h"


APCBase::APCBase()
	: ActiveFrameRate(30), NotInFocusFrameRate(5), MainWidgetClass(nullptr) {
	PrimaryActorTick.bCanEverTick = false;
}

void APCBase::BeginPlay() {
	Super::BeginPlay();

	// Main widget was not set, close the game
	if (!MainWidgetClass) {
		UE_LOG(LogTemp, Error,
		       TEXT("Game closed (MainWidgetClass not set). Create a blueprint and reference your widget in it."));
		UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
		return;
	}

	// Graphics settings
	TArray<FString> GraphicsSettings = {
		"sg.PostProcessQuality 0", "sg.ShadowQuality 0", "sg.TextureQuality 0", "sg.EffectsQuality 0", "r.DetailMode 0",
		"FoliageQuality 0"
	};

	for (const auto& setting : GraphicsSettings) {
		ConsoleCommand(setting);
	}

	// Display the main widget
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);

	GetGameInstance()->GetGameViewportClient()->GetWindow()->SetWindowMode(EWindowMode::Windowed);

	MainWidgetInstance = CreateWidget<UUserWidget>(this, MainWidgetClass);
	MainWidgetInstance->AddToViewport();

	FSlateApplication::Get().OnApplicationActivationStateChanged().AddUObject(this, &APCBase::OnWindowFocusChanged);
}

void APCBase::OnWindowFocusChanged(bool bIsActive) {
#if !WITH_EDITOR
	if (bIsActive) {
		GEngine->SetMaxFPS(ActiveFrameRate);
		UE_LOG(LogTemp, Warning, TEXT("Active FPS: %d"), ActiveFrameRate);
	}
	else {
		GEngine->SetMaxFPS(NotInFocusFrameRate);
		UE_LOG(LogTemp, Warning, TEXT("InActive FPS: %d"), NotInFocusFrameRate);
	}
#endif
}
