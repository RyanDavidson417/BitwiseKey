
#include "Interactables/BWK_DoubleJump.h"
#include "PlayerCharacter.h"

void UDoubleJump::CollectPowerup(APlayerController* PlayerController)
{
	if (IsValid(gs)) {
		gs->DoubleJumpData->bCollected = true;
		PlayerController->GetCharacter()->JumpMaxCount =
			gs->DoubleJumpData->ActiveValue;

	}
}

void UDoubleJump::Reset()
{
    UE_LOG(LogTemp, Warning, TEXT("jump reset"))
    if (IsValid(gs)) {
        gs->DoubleJumpData->bCollected = false;

        if (IsValid(MPlayerController)) {
            MPlayerController->GetCharacter()->JumpMaxCount
                = gs->DoubleJumpData->defaultValue;
        }
    }
}

