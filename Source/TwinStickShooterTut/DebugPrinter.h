// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */
class TWINSTICKSHOOTERTUT_API DebugPrinter
{
public:


	DebugPrinter();
	~DebugPrinter();

	static void Print(const char* Message, const bool bPrintToScreen = true, const bool bPrintToLog = true);
};
