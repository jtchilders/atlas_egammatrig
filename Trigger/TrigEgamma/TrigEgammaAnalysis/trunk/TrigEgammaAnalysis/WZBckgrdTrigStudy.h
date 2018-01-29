
#ifndef _WZBCKGRDTRIGSTUDY_H
#define _WZBCKGRDTRIGSTUDY_H

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

// Offline jet, met containers
#include "MissingETEvent/MissingET.h"
#include "JetEvent/JetCollection.h"


class TH1F;
class TH2F;
class ElectronCuts;
class ElectronList;
class TrigElectronPlots;
class L2vsOfflineElectronPlots;
class EfficiencyPlot;
class WZHistos;
class WZCuts;
class WZHistoList;

class WZBackgroudTriggerStudy: public AthAlgorithm{
public:
   // These are the standard Athena public member functions.
   WZBackgroudTriggerStudy(const std::string& name, ISvcLocator* pSvcLocator);
   virtual ~WZBackgroudTriggerStudy();

   virtual StatusCode initialize();
   virtual StatusCode execute();
   virtual StatusCode finalize();
   
private:
   WZBackgroudTriggerStudy();
   WZBackgroudTriggerStudy(const WZBackgroudTriggerStudy& rhs);
   void operator=(const WZBackgroudTriggerStudy& rhs);
   
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
   const JetCollection*              m_offlineJets;
   const MissingET*                  m_offlineMet;
   
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
   std::string m_offlineJetsLocation;
   std::string m_offlineMetLocation;
   
   StatusCode LoadContainers(void);
   
   // Trigger Tools
   ToolHandle<Trig::TrigDecisionTool> m_trigger; // Use the trigger
   ToolHandle<TrigMatchTool> m_trigMatch; // Use the trigger chain matching tool
   
   StatusCode LoadTools(void);
   
   // Histogramming Service
   ITHistSvc*   m_histoSvc;
   WZHistos*    m_histos;
   WZCuts*      m_cuts;
   WZHistoList* m_histoList;
   
   // returns the best matched TrigElectron for an offline electron and
   // a given chain
   const TrigMatch::TrigElectronL2* GetMatchedL2Electron(Analysis::Electron *electron,std::string l2chain,float radius);
   const TrigMatch::TrigElectronEF* GetMatchedEFElectron(Analysis::Electron *electron,std::string EFchain,float radius);
   
   // check that there is one vertex + 3 tracks
   static const unsigned int m_numPrimaryVertex = 1;
   static const unsigned int m_numTrksAtPrimVertex = 3;
   static const unsigned int m_vertexPosition = 100;
   
   // MET cut
   float m_missingEtCut;
   
   
   // Calculate M_INV
   float GetInvariantMass(Analysis::Electron *e1,Analysis::Electron *e2);
   
   bool IsIsolated(Analysis::Electron const *e,const unsigned short int& electroni,
      std::vector< std::pair<unsigned short int,unsigned short int> >& overlappingJets,
      const float dr = 0.5) const;
   bool IsIsolatedJet(unsigned short int& jeti,
         std::vector< std::pair<unsigned short int,unsigned short int> >& overlappingElectronJetList) const;
   
   std::map<unsigned short int,unsigned short int>* FindOverlappingElectronsAndJets(std::vector<unsigned short int>& electron,std::vector<unsigned short int>& jet,double dr_min);
   
   template<class T>
   double radius(T const * obj){
      return sqrt( obj->eta()*obj->eta() + obj->phi()*obj->phi() );
   }
   
   double TransverseMass(Analysis::Electron const * electron,MissingET const *met);
   
   std::string m_s_e20_loose;
   std::string m_s_e20_medium;
   std::string m_s_e20_medium1;
   std::string m_s_e20_medium2;
   std::string m_s_e20_tight;
   std::string m_s_e22_loose;
   std::string m_s_e22_medium;
   std::string m_s_e22_medium1;
   std::string m_s_e22_medium2;
   std::string m_s_e22_tight;
   
   std::string m_s_e20_looseTrk;
   std::string m_s_e20_loose1;
   std::string m_s_e20_loose_2j10_a4tc_EFFS;
   std::string m_s_e20_loose_3j10_a4tc_EFFS;
   std::string m_s_e20_loose_4j10_a4tc_EFFS;
   
   
   unsigned int m_n_events;
   unsigned int m_n_electrons;
   unsigned int m_evtPassingVertex;
   unsigned int m_elPassingPt;
   unsigned int m_elPassingEta;
   unsigned int m_elPassingMedNotTight;
   unsigned int m_elPassingTightNotMed;
   unsigned int m_elPassingMedium;
   unsigned int m_elPassingTight;
   unsigned int m_elPassingIsolation;
   
   
   static const float PI;
};





#endif

