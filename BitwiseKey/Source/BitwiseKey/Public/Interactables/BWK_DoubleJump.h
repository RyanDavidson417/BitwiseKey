

#pragma once

#include "coreminimal.h"
#include "Interactables/PowerupCollectibleBase.h"
#include "BWK_DoubleJump.generated.h"


UCLASS(ClassGroup = ("Powerups"), meta = (BlueprintSpawnableComponent))
class BITWISEKEY_API UDoubleJump : public UPowerupCollectibleBase 
{
	GENERATED_BODY()

public:
	void CollectPowerup(APlayerController* PlayerController) override;
	virtual void Reset() override;
};