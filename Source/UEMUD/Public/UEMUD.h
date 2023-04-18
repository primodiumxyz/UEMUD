#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUEMUDModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
