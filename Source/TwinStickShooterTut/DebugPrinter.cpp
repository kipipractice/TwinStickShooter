// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugPrinter.h"
#include "Engine.h"

DebugPrinter::DebugPrinter()
{
}

DebugPrinter::~DebugPrinter()
{
}

void DebugPrinter::Print(const char* Message, EMessageType MessageType, const bool bPrintToScreen /*= true*/, const bool bPrintToLog /*= true*/)
{
#ifdef WITH_EDITOR
	if (bPrintToScreen && GEngine) {
		switch (MessageType) {
			case EMessageType::Info:
				GEngine->AddOnScreenDebugMessage(-1, DebugPrinter::MESSAGE_LENGTH, FColor::Blue, FString(UTF8_TO_TCHAR(Message)));
				break;
			case EMessageType::Warning:
				GEngine->AddOnScreenDebugMessage(-1, DebugPrinter::MESSAGE_LENGTH, FColor::Yellow, FString(UTF8_TO_TCHAR(Message)));
				break;
			case EMessageType::Error:
				GEngine->AddOnScreenDebugMessage(-1, DebugPrinter::MESSAGE_LENGTH, FColor::Red, FString(UTF8_TO_TCHAR(Message)));
				break;
		}
	}
#endif
	if (bPrintToLog) {
		switch (MessageType) {
		case EMessageType::Info:
			UE_LOG(LogTemp, Log, TEXT("%s"), *FString(UTF8_TO_TCHAR(Message)))
			break;
		case EMessageType::Warning:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(UTF8_TO_TCHAR(Message)))
			break;
		case EMessageType::Error:
			UE_LOG(LogTemp, Error, TEXT("%s"), *FString(UTF8_TO_TCHAR(Message)))
			break;
		}
	}
}
