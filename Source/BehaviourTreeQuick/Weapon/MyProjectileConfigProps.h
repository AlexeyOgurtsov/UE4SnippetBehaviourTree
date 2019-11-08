#pragma once

#include "Util/Audio/HelperAudioTypes.h"
#include "MyProjectileConfigProps.generated.h"

USTRUCT(BlueprintType, Category=Projectile)
struct FMyProjectileAudioConfigProps
{
	GENERATED_BODY()

	/** HitSound*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Projectile)
	FMySoundProps HitSound;

	/** FlySound*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Projectile)
	FMySoundMultiplierProps FlyMultiplier;
};


USTRUCT(BlueprintType, Category=Projectile)
struct FMyProjectileConfigProps
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	FMyProjectileAudioConfigProps Audio;
};

