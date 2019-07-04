// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugPrinter.h"
#include "Engine.h"

DebugPrinter::DebugPrinter()
{
}

DebugPrinter::~DebugPrinter()
{
}

void DebugPrinter::Print(const char* Message, const bool bPrintToScreen /*= true*/, const bool bPrintToLog /*= true*/)
{
#ifdef WITH_EDITOR
	if (bPrintToScreen && GEngine != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString(UTF8_TO_TCHAR(Message)));
	}
	if (bPrintToLog) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(UTF8_TO_TCHAR(Message)))
	}
#endif
}
