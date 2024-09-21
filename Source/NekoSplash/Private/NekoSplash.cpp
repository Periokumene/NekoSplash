#include "NekoSplash.h"

#include "NekoSplashSettings.h"

#define LOCTEXT_NAMESPACE "FNekoSplashModule"

DEFINE_LOG_CATEGORY(LogNekoSplash)

void FNekoSplashModule::
StartupModule()
{
	UNekoSplashSettings::Get()->ExecuteRandomSplash();
}


void FNekoSplashModule::
ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNekoSplashModule, NekoSplash)