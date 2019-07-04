// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsSaveGame.h"
#include "InputType.h"

USettingsSaveGame::USettingsSaveGame() {
	this->Type = InputType::PC;
	this->SaveSlotName = "Settings";
	this->UserIndex = 0;
}

FString USettingsSaveGame::GetSaveSlotName() {
	return SaveSlotName;
}

uint32 USettingsSaveGame::GetUserIndex() {
	return UserIndex;
}