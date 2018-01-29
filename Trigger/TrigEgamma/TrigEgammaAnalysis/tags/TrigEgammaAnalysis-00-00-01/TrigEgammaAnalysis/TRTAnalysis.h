
#ifndef _TRIGEGAMMATRTANALYSIS_H
#define _TRIGEGAMMATRTANALYSIS_H

// Athena includes
#include "AthenaBaseComps/AthAlgorithm.h"
#include "GaudiKernel/MsgStream.h"
#include "StoreGate/StoreGateSvc.h"
#include "GaudiKernel/ITHistSvc.h"
#include "CLHEP/Units/SystemOfUnits.h"


// Event info
#include "EventInfo/EventInfo.h"
#include "EventInfo/EventID.h"

// Trigger Menu tools
#include "TrigObjectMatching/TrigMatchTool.h"

// Egamma includes
#include "AnalysisTriggerEvent/LVL1_ROI.h"
#include "TrigCaloEvent/TrigTauClusterContainer.h"
#include "egammaEvent/egammaContainer.h"
#include "TrigParticle/TrigElectronContainer.h"
#include "TrigParticle/TrigPhotonContainer.h"
#include "egammaEvent/ElectronContainer.h"
#include "egammaEvent/PhotonContainer.h"
#include "egammaEvent/Electron.h"
#include "VxVertex/VxContainer.h"


class TrigEgammaTRTAnalysis: public AthAlgorithm{
public:
   // These are the standard Athena public member functions.
   TrigEgammaTRTAnalysis(const std::string& name, ISvcLocator* pSvcLocator);
   virtual ~TrigEgammaTRTAnalysis();

   virtual StatusCode initialize();
   virtual StatusCode execute();
   virtual StatusCode finalize();
   
private:
   TrigEgammaTRTAnalysis();
   TrigEgammaTRTAnalysis(const TrigEgammaTRTAnalysis& rhs);
   void operator=(const TrigEgammaTRTAnalysis& rhs);
   
   // log messages
   MsgStream* m_log;
   
   // Store Gate service
   ServiceHandle<StoreGateSvc> m_storeGate;
   
   // Objects retrieved from Store Gate
   const EventInfo*                  m_eventInfo;
   const LVL1_ROI*                   m_lvl1RoIs;
   const TrigElectronContainer*      m_l2Electrons;
   const egammaContainer*            m_efElectrons;
   const ElectronContainer*          m_offlineElectrons;
   const CaloClusterContainer*       m_offlineClusters;
   const TrigPhotonContainer*        m_l2Photons;
   const egammaContainer*            m_efPhotons;
   const PhotonContainer*            m_offlinePhotons;
   const VxContainer*                m_primaryVertex;
   // names of these objects
   std::string m_lvl1RoIsLocation;
   std::string m_l2ElectronsLocation;
   std::string m_efElectronsLocation;
   std::string m_offlineElectronsLocation;
   std::string m_offlineClustersLocation;
   std::string m_l2PhotonsLocation;
   std::string m_efPhotonsLocation;
   std::string m_offlinePhotonsLocation;
   std::string m_PrimaryVertexLocation;
   
   void ZeroContainerPointers(void);
   StatusCode LoadContainers(void);
   
   // Trigger Tools
   ToolHandle<Trig::TrigDecisionTool> m_trigger; // Use the trigger
   ToolHandle<TrigMatchTool> m_trigMatch; // Use the trigger chain matching tool
   
   StatusCode LoadTools(void);
   
   // Histogramming Service
   ITHistSvc* m_histoSvc;
   
   
};




#endif

