#include "MyGunEnemy.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"

AMyGunEnemy::AMyGunEnemy()
{
}

void AMyGunEnemy::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}

bool AMyGunEnemy::FireGun()
{
	if( ! IsValidWeaponConfig() )
	{
		return false;
	}

	if(CanFire())
	{
		return DoFire();
	}
	return false;
}

bool AMyGunEnemy::IsValidWeaponConfig() const
{
	if(nullptr == GunConfig.ProjectileClass)
	{
		M_LOG_ERROR(TEXT("Wrong weapon config: ProjectileClass is NULL"));
		return false;
	}

	if( GunConfig.GunSocketName.IsNone() )
	{
		M_LOG_ERROR(TEXT("Wrong weapon config: socket name is NONE"));
		return false;
	}

	return true;
}

bool AMyGunEnemy::DoFire()
{
	M_LOGFUNC();

	FTransform const LaunchTransform = GetProjectileLaunchTransform();

	FActorSpawnParameters SpawnParams;
	AActor* const Projectile = GetWorld()->SpawnActor(GunConfig.ProjectileClass, &LaunchTransform, SpawnParams);
	if( ! IsValid(Projectile) )
	{
		M_LOG_ERROR(TEXT("Unable to launch projectile of class \"%s\": IsValid() returned false for the spawned projectile actor"), *GunConfig.ProjectileClass->GetName());
		return false;
	}

	LastShotTime = GetWorld()->GetTimeSeconds();

	return true;
}

bool AMyGunEnemy::CanFire() const
{
	float const NextAllowedShotTime = LastShotTime + GunConfig.MinFireInterval;
	if(GetWorld()->GetTimeSeconds() < NextAllowedShotTime)
	{
		return false;
	}
	return true;
}

FTransform AMyGunEnemy::GetProjectileLaunchTransform() const
{
	FTransform const DefaultTransform = GetActorTransform();

	UStaticMeshComponent* const SMComponent = FindComponentByClass<UStaticMeshComponent>();
	if(SMComponent == nullptr)
	{
		M_LOG_ERROR(TEXT("Unable to find static mesh!"));
		return DefaultTransform;
	}

	const UStaticMeshSocket* const Socket = SMComponent->GetSocketByName(GunConfig.GunSocketName);
	FTransform LaunchTransform; 
	bool const bTransformFound = Socket->GetSocketTransform(/**out**/LaunchTransform, SMComponent);
	if( ! bTransformFound )
	{
		M_LOG_ERROR(TEXT("Unable to calculate socket transform!"));
		return DefaultTransform;
	}
	ULogUtilLib::LogTransformC(TEXT("LaunchTransform"), LaunchTransform);
	return LaunchTransform;
}
