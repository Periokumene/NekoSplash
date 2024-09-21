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

	bool CollectImages_Web  (TArray<FString>& Paths) const;
	bool CollectImages_Local(TArray<FString>& Paths) const;

	void    ExecuteRandomSplash() const;
	FString QueryPictureRandomly() const;
	
	
	UPROPERTY(EditAnywhere, Config, Category="Splash")
	bool bSwitchSplash = true;

private:
	UPROPERTY(EditAnywhere, Config, Category="Splash", DisplayName="Web API URL")
	FString WebAPIUrl;

	UPROPERTY(EditAnywhere, Config, Category="Splash", DisplayName="Save Web Image to library")
	bool bSaveWebImageToLocal;
	
	UPROPERTY(EditAnywhere, Config, Category="Splash", meta=(EditCondition="bSwitchSplash"))
	FDirectoryPath PictureLibrary;
};
