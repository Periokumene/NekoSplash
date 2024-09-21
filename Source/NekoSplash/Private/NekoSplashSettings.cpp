#include "NekoSplashSettings.h"

#include "EditorDirectories.h"
#include "NekoSplash.h"

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


FString UNekoSplashSettings::
QueryPictureRandomly() const
{
	if (FPaths::DirectoryExists(SplashPictureLibrary.Path))
	{
		const FString FilePattern = TEXT("*.png");
		TArray<FString> FoundFiles;
		IFileManager& FileManager = IFileManager::Get();
		FileManager.FindFiles(FoundFiles, *FPaths::Combine(SplashPictureLibrary.Path, FilePattern), true, false);

		if (FoundFiles.Num())
		{
			const int32 Index = FMath::RandRange(0, FoundFiles.Num() - 1);
			return FPaths::Combine(SplashPictureLibrary.Path, FoundFiles[Index]);
		}
		UE_LOG(LogNekoSplash, Error, TEXT("QueryPictureRandomly: No pictures fond under directory!"))
		return TEXT("");
	}
	UE_LOG(LogNekoSplash, Error, TEXT("QueryPictureRandomly: Invalid library directory!"))
	return TEXT("");
}


void UNekoSplashSettings::
PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UNekoSplashSettings, bPostChangeTrigger))
	{
		const FString PicPath = QueryPictureRandomly();
		if (!PicPath.IsEmpty()){
			FEditorDirectories::Get().SetLastDirectory(ELastDirectory::GENERIC_OPEN, FPaths::GetPath(PicPath));
		}
	}
}
