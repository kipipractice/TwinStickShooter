// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsSaveGame.h"
#include "InputType.h"

USettingsSaveGame::USettingsSaveGame() {
	this->Type = InputType::PC;
	this->SaveSlotName = SettingsSaveName;
	this->UserIndex = SaveSlotIndex;
}

FString USettingsSaveGame::GetSaveSlotName() {
	return SaveSlotName;
}

uint32 USettingsSaveGame::GetUserIndex() {
	return UserIndex;
}