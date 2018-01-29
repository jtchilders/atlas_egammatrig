#ifndef _OFFLINEELECTRONSELECTOR_H_
#define _OFFLINEELECTRONSELECTOR_H_


#include <vector>

#include "AthenaBaseComps/AthAlgorithm.h"
#include "egammaEvent/ElectronContainer.h"
#include "StoreGate/StoreGateSvc.h"

class NtupEvent;

class OfflineElectronSelectorAlg : public AthAlgorithm
{
public:
   // These are the standard Athena public member functions.
   OfflineElectronSelectorAlg(const std::string& name, ISvcLocator* pSvcLocator);
   virtual ~OfflineElectronSelectorAlg();
   
   virtual StatusCode initialize();
   virtual StatusCode execute();
   virtual StatusCode finalize();
   
   

protected:
   
   // Store Gate service
   ServiceHandle<StoreGateSvc> m_storeGate;
   
   const ElectronContainer* m_offlineElectrons;
   std::string              m_offlineElectronsName;
   
   double m_electronEtCut;
   bool   m_useEtCut;
   double m_electronEtaCut;
   bool   m_useEtaCut;
   
   unsigned int m_n_events;
};

#endif
