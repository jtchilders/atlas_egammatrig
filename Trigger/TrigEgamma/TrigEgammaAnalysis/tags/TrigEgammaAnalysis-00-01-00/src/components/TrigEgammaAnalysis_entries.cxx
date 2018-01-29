#include "TrigEgammaAnalysis/TRTAnalysis.h"
#include "TrigEgammaAnalysis/ZeeTagAndProbeAnalysis.h"
#include "TrigEgammaAnalysis/WZBckgrdTrigStudy.h"
#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_ALGORITHM_FACTORY( TrigEgammaTRTAnalysis )
DECLARE_ALGORITHM_FACTORY( TrigEgammaZeeTagAndProbeAnalysis )
DECLARE_ALGORITHM_FACTORY( WZBackgroudTriggerStudy )

DECLARE_FACTORY_ENTRIES( TrigEgammaAnalysis ) {
DECLARE_ALGORITHM( TrigEgammaTRTAnalysis );
DECLARE_ALGORITHM( TrigEgammaZeeTagAndProbeAnalysis );
DECLARE_ALGORITHM( WZBackgroudTriggerStudy );
}
