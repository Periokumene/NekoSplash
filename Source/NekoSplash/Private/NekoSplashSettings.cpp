#include "NekoSplashSettings.h"

#include "NekoSplash.h"
#include "SourceControlHelpers.h"

#include "DetailCustomizations/Private/WindowsTargetSettingsDetails.cpp"

const UNekoSplashSettings* UNekoSplashSettings::
Get()
{
	return GetDefault<UNekoSplashSettings>();
}


UNekoSplashSettings* UNekoSplashSettings::
GetMutable()
{
	return GetMutableDefault<UNekoSplashSettings>();
}


bool UNekoSplashSettings::
CollectImages_Web(TArray<FString>& Paths) const
{
	return false;
}


bool UNekoSplashSettings::
CollectImages_Local(TArray<FString>& Paths) const
{
	// It's already IgnoreCase
	TArray<FString> PatternList = {
		TEXT("*.png"),
		TEXT("*.jpg"),
		TEXT("*.bmp"),
	};
	
	for (const FString& FilePattern : PatternList)
	{
		TArray<FString> FileNames;
		IFileManager& FileManager = IFileManager::Get();
		FileManager.FindFiles(FileNames, *FPaths::Combine(PictureLibrary.Path, FilePattern), true, false);
		for (const FString& FileName : FileNames){
			Paths.Add(FPaths::Combine(PictureLibrary.Path, FileName));
		}
	}

	return Paths.Num() > 0;
}


FString UNekoSplashSettings::
QueryPictureRandomly() const
{
	auto RandomPick = [](const TArray<FString>& Paths) -> FString
	{
		if (Paths.Num() > 0)
		{
			const int32 Index = FMath::RandRange(0, Paths.Num() - 1);
			return Paths[Index];
		}
		return TEXT("");
	};
	
	TArray<FString> WebImages;
	TArray<FString> LocalImages;

	if (!WebAPIUrl.IsEmpty()){
		if (CollectImages_Web(WebImages)){
			return RandomPick(WebImages);
		}
	}
	if (FPaths::DirectoryExists(PictureLibrary.Path)){
		if (CollectImages_Local(LocalImages)){
			return RandomPick(LocalImages);
		}
	}
	
	UE_LOG(LogNekoSplash, Error, TEXT("QueryPictureRandomly: Fail to get any pictures"))
	return TEXT("");
}


void UNekoSplashSettings::
ExecuteRandomSplash() const
{
	const FString TargetImagePath  = GetWindowsSplashFilename(EWindowsImageScope::GameOverride, true);
	const FString DefaultImagePath = GetWindowsSplashFilename(EWindowsImageScope::Engine, true);
	const FString TargetImagePathNoEx = FPaths::GetPath(TargetImagePath) / FPaths::GetBaseFilename(TargetImagePath);

	const FString NewSourceImagePath = QueryPictureRandomly();
	if (NewSourceImagePath.IsEmpty()){
		return;
	}

	FString NewTargetImagePath = TargetImagePath;
	if (FPaths::GetExtension(TargetImagePath) != FPaths::GetExtension(NewSourceImagePath))
	{
		IFileManager& FileManager = IFileManager::Get();
		constexpr bool bRequireExists = false;
		constexpr bool bEvenIfReadOnly = true;
		constexpr bool bQuiet = true;
		FileManager.Delete(*TargetImagePath, bRequireExists, bEvenIfReadOnly, bQuiet);
		
		NewTargetImagePath = TargetImagePathNoEx + TEXT(".") + FPaths::GetExtension(NewSourceImagePath);
		ensureMsgf(
			FileManager.Copy(*NewTargetImagePath, *NewSourceImagePath, true, true) == COPY_OK,
			TEXT("Fail to override file %s"), *NewSourceImagePath);
	}
}
