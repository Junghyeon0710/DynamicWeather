// Copyright Epic Games, Inc. All Rights Reserved.

#include "DynamicWeatherEditorModule.h"

#include "DynamicWeatherTimeDetailsCustomization.h"


#define LOCTEXT_NAMESPACE "FDynamicWeatherEditorModule"

void FDynamicWeatherEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout("DynamicWeatherTime", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDynamicWeatherTimeDetailsCustomization::MakeInstance));


}

void FDynamicWeatherEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDynamicWeatherEditorModule, DynamicWeatherEditor)