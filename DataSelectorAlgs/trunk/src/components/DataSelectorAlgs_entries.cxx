#include "DataSelectorAlgs/TriggerSelectorAlg.h"
#include "DataSelectorAlgs/OfflineElectronSelectorAlg.h"
#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_ALGORITHM_FACTORY( TriggerSelectorAlg )
DECLARE_ALGORITHM_FACTORY( OfflineElectronSelectorAlg )

DECLARE_FACTORY_ENTRIES( DataSelectorAlgs ) {
DECLARE_ALGORITHM( TriggerSelectorAlg );
DECLARE_ALGORITHM( OfflineElectronSelectorAlg );
}
