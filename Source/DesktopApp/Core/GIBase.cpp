// Fill out your copyright notice in the Description page of Project Settings.


#include "GIBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameUserSettings.h"

UGIBase::UGIBase() {
	FrameRate = 30;
	MainWidgetClass = nullptr;
	MainWidgetInstance = nullptr;
	PlayerController = nullptr;
}

void UGIBase::Init() {
	Super::Init();

	// To get the player controller in the GameInstance earlier
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGIBase::StartLogic);

	/**
	 * Hacky way so the FPostLoadMapDelegate will trigger
	 * Since it doesn't when you open the game
	 */
	GetWorld()->ServerTravel("/Game/Core/Main");
}

void UGIBase::StartLogic(UWorld* Map) {
	PlayerController = GetWorld()->GetFirstPlayerController();

	// Main widget was not set, close the game
	if (!MainWidgetClass) {
		UE_LOGFMT(LogTemp, Error, "Game closed (MainWidgetClass not set). Create a blueprint and reference your widget in it.");
		UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
		return;
	}

	// Graphics settings
	TArray<FString> GraphicsSettings = {"sg.PostProcessQuality 0", "sg.ShadowQuality 0", "sg.TextureQuality 0", "sg.EffectsQuality 0", "r.DetailMode 0", "FoliageQuality 0"};

	for (const auto &setting : GraphicsSettings) {
		PlayerController->ConsoleCommand(setting);
	}

	if (UKismetSystemLibrary::IsPackagedForDistribution()) {
		PlayerController->ConsoleCommand("t.maxfps " + FString::FromInt(FrameRate));
	}

	// Display the main widget
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);

	GetGameViewportClient()->GetWindow()->SetWindowMode(EWindowMode::Windowed);

	MainWidgetInstance = CreateWidget<UUserWidget>(this, MainWidgetClass);
	MainWidgetInstance->AddToViewport();

	UE_LOG(LogTemp, Warning, TEXT("GIBase::StartLogic"));
}
