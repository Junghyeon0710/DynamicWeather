#include "ProceduralTimers/RainActivationTimer.h"

void FRainActivationTimer::BuildSequence(UProceduralDayTimerBuilder* InBuilder)
{
	FProceduralDayTimer::BuildSequence(InBuilder);
}

// void FRainActivationTimer::OnDayTimerEvent(float CurrentTimeOfDay)
// {
// 	FNiagaraActivationTimerBase::OnDayTimerEvent(CurrentTimeOfDay);
// }
