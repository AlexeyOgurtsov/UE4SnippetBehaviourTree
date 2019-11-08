#pragma once

#include "MyEnemyPawnBase.h"
#include "MyGunEnemy.generated.h"

USTRUCT(BlueprintType, Category=Misc)
struct FMyGunConfig
{
	GENERATED_BODY()
	
	/** GunSocket*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName GunSocketName = FName(TEXT("Gun"));

	/** ProjectileClass*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ProjectileClass;

	/** MinFireInterval*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFireInterval = 1.0F;
};

UCLASS()
class AMyGunEnemy : public AMyEnemyPawnBase
{
	GENERATED_BODY()

public:
	AMyGunEnemy();

	virtual void BeginPlay() override;
	
	// ~ Weapon Begin
	/** IsValidWeaponConfig*/
	UFUNCTION(BlueprintPure, Category=Weapon)
	bool IsValidWeaponConfig() const;
	
	/** GetProjectileLaunchTransform*/
	UFUNCTION(BlueprintPure, Category=Weapon)
	FTransform GetProjectileLaunchTransform() const;
	
	/** FireGun*/
	UFUNCTION(BlueprintCallable, Category=Weapon)
	bool FireGun();

	/** CanFire*/
	UFUNCTION(BlueprintCallable, Category=Weapon)
	bool CanFire() const;
	
	/** GetGunConfig*/
	UFUNCTION(BlueprintPure, Category=Weapon)
	FMyGunConfig GetGunConfig() const
	{
		return GunConfig;
	}
	
	/** GetLastShotTime*/
	UFUNCTION(BlueprintPure, Category=Weapon)
	float GetLastShotTime() const
	{
		return LastShotTime;
	}
	// ~ Weapon End

private:
	// ~ Gun Begin
	/** GunConfig*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Weapon)
	FMyGunConfig GunConfig;

	/** LastShotTime*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Weapon)
	float LastShotTime = 0.0F;

	bool DoFire();
	// ~ Gun End
};

// ~ RightHere_AMyGunEnemy Begin



// Adhoc impl lines (WARNING! move to .cpp file, otherwise will fail to compile!)
// ~ RightHere_AMyGunEnemy End

