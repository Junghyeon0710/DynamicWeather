#include "ProceduralTimers/NiagaraActivationTimerBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Actors/BaseDayActor.h"

void FNiagaraActivationTimerBase::BuildSequence(UProceduralDayTimerBuilder* InBuilder)
{
	FProceduralDayTimer::BuildSequence(InBuilder);
}

void FNiagaraActivationTimerBase::DeActivateNiagara() const
{
	if (IsValid(NiagaraComponent) && NiagaraComponent->IsActive())
	{
		NiagaraComponent->Activate(false);
	}
}

void FNiagaraActivationTimerBase::OnDayTimerEvent(float CurrentTimeOfDay)
{
	if (ensure(!NiagaraSystem))
	{
		UE_LOG(LogTemp, Error, TEXT("Niagara is not set!"));
		return;
	}

	ABaseDayActor* TargetActor = WeakTargetActor.Get();
	
	if (!TargetActor)
	{
		UE_LOG(LogTemp, Error, TEXT("TargetActor is not set!"));
		return;
	}
	
	if (!IsValid(NiagaraComponent))
	{
		// 1. NiagaraComponent 생성
		NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
		NiagaraSystem,                                      // Niagara System Asset
		TargetActor->GetRootComponent(),              // Parent Component
		NAME_None,                                    // Socket name
		FVector::ZeroVector,                          // Relative Location
		FRotator::ZeroRotator,                        // Relative Rotation
		EAttachLocation::KeepRelativeOffset,
		false,                                         // Auto Destroy
		true                                          // Auto Activate
	);
	}

	if (NiagaraComponent->IsActive())
	{
		return;
	}

	// 2. (선택적) 파라미터 설정 등 추가 설정 가능
	// NiagaraComp->SetVariableFloat(TEXT("SomeParam"), Value);

	// 3. (이미 활성화된 상태일 수 있지만 명시적으로)
	NiagaraComponent->Activate(true);
}
