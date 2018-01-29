
#ifndef _TRIGEGAMMAZEETAGANDPROBEANALYSIS_H
#define _TRIGEGAMMAZEETAGANDPROBEANALYSIS_H

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
#include "TrigDecisionTool/TrigDecisionTool.h"
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


class TH1F;
class TH2F;
class ElectronCuts;
class ElectronList;
class TrigElectronPlots;
class L2vsOfflineElectronPlots;

class TrigEgammaZeeTagAndProbeAnalysis: public AthAlgorithm{
public:
   // These are the standard Athena public member functions.
   TrigEgammaZeeTagAndProbeAnalysis(const std::string& name, ISvcLocator* pSvcLocator);
   virtual ~TrigEgammaZeeTagAndProbeAnalysis();

   virtual StatusCode initialize();
   virtual StatusCode execute();
   virtual StatusCode finalize();
   
private:
   TrigEgammaZeeTagAndProbeAnalysis();
   TrigEgammaZeeTagAndProbeAnalysis(const TrigEgammaZeeTagAndProbeAnalysis& rhs);
   void operator=(const TrigEgammaZeeTagAndProbeAnalysis& rhs);
   
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
   
   StatusCode BookHistos(void);
   
   // My histogramming
   TH1F *m_h1f_inv_mass_ee;
   TH1F *m_h1f_tag_et;
   TH1F *m_h1f_tag_eta;
   TH1F *m_h1f_tag_phi;
   TH1F *m_h1f_tag_etcone30;
   
   TH1F *m_h1f_probe_et;
   TH1F *m_h1f_probe_eta;
   TH1F *m_h1f_probe_phi;
   TH1F *m_h1f_probe_etcone30;
   
   TH1F *m_h1f_probe_et_privx;
   
   TH1F *m_h1f_probe_et_EF_e20_loose;
   TH1F *m_h1f_probe_et_privx_EF_e20_loose;
   
   TH1F *m_h1f_probe_et_L2_e20_loose;
   
   TH2F *m_h2f_probe_noL2e_etaPhi;
   
   TrigElectronPlots *m_trigE_probe_L2_e20_loose;
   TrigElectronPlots *m_trigE_probe_L2_e20_loose_Zee;
   
   L2vsOfflineElectronPlots *m_l2vsOff_probe_L2_e20_loose;
   L2vsOfflineElectronPlots *m_l2vsOff_probe_L2_e20_loose_Zee;
   
   // returns the best matched TrigElectron for an offline electron and
   // a given chain
   const TrigMatch::TrigElectronL2* GetMatchedL2Electron(Analysis::Electron *electron,std::vector<const TrigMatch::TrigElectronL2*>& trigElectrons);
         
   // check that there is one vertex + 3 tracks
   bool HasMinimumVertices(void) const;
   static const unsigned int m_numPrimaryVertex = 1;
   static const unsigned int m_numTrksAtPrimVertex = 3;
   static const unsigned int m_vertexPosition = 100;
   
   // Calculate M_INV
   float GetInvariantMass(Analysis::Electron *e1,Analysis::Electron *e2);
   
   // tag and probe variables
   ElectronCuts *m_tagCuts;
   ElectronList *m_tagList;
   
   ElectronCuts *m_probeCuts;
   ElectronList *m_probeList;
   
   // Count number of tag and probe electrons
   unsigned int m_nProbes;
   unsigned int m_nProbes_L2_e20_loose;
   unsigned int m_nProbes_EF_e20_loose;
   unsigned int m_nTags;
};




#endif

