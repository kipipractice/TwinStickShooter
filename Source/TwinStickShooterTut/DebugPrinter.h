// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */
UENUM()
enum class EMessageType : uint8
{
	Info,
	Warning,
	Error
};

class TWINSTICKSHOOTERTUT_API DebugPrinter
{
public:


	DebugPrinter();
	~DebugPrinter();

	static void Print(const char* Message, EMessageType MessageType = EMessageType::Info, const bool bPrintToScreen = true, const bool bPrintToLog = true);


private:
	static constexpr float MESSAGE_LENGTH = 5.0f;

};
