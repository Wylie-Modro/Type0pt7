// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Type0pt7GameMode.h"
#include "Type0pt7Character.h"
#include "UObject/ConstructorHelpers.h"

AType0pt7GameMode::AType0pt7GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
