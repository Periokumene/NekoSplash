#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "NekoSplashSettings.generated.h"


UCLASS(Config=NekoSplash, DefaultConfig)
class UNekoSplashSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static const UNekoSplashSettings* Get();
	static UNekoSplashSettings*       GetMutable();
	FString QueryPictureRandomly() const;

private:
	UPROPERTY(EditAnywhere, Config, Category="Splash")
	bool bSwitchSplash;

	UPROPERTY(EditAnywhere, Config, Category="Splash", meta=(EditCondition="bSwitchSplash"))
	FDirectoryPath SplashPictureLibrary;


	UPROPERTY(EditAnywhere, Category="Debug")
	bool bPostChangeTrigger;

	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
