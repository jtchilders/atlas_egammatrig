#include "TrigEgammaAnalysis/TRTAnalysis.h"
#include "TrigEgammaAnalysis/ZeeTagAndProbeAnalysis.h"
#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_ALGORITHM_FACTORY( TrigEgammaTRTAnalysis )
DECLARE_ALGORITHM_FACTORY( TrigEgammaZeeTagAndProbeAnalysis )

DECLARE_FACTORY_ENTRIES( TrigEgammaAnalysis ) {
DECLARE_ALGORITHM( TrigEgammaTRTAnalysis );
DECLARE_ALGORITHM( TrigEgammaZeeTagAndProbeAnalysis );
}
