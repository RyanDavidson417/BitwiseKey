// Fill out your copyright notice in the Description page of Project Settings.


#include "BitwiseGameState.h"


ABitwiseGameState::ABitwiseGameState()
{
	EA_PowerupOrder.Add(EPowerUp::PE_XRay);
	EA_PowerupOrder.Add(EPowerUp::PE_Invisibility);
	EA_PowerupOrder.Add(EPowerUp::PE_Teleport);
	EA_PowerupOrder.Add(EPowerUp::PE_Movement);
}
