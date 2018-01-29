
#include "TrigEgammaAnalysis/WZBckgrdTrigStudy.h"
#include "TrigEgammaAnalysis/ElectronList.h"
#include "TrigEgammaAnalysis/ElectronCuts.h"
#include "TrigEgammaAnalysis/EfficiencyPlot.h"
#include "TrigEgammaAnalysis/L2vsOfflineElectronPlots.h"
#include "TrigEgammaAnalysis/TrigElectronPlots.h"
#include "TrigEgammaAnalysis/HistogramManager.h"
#include "TrigEgammaAnalysis/WZHistos.h"
#include "TrigEgammaAnalysis/WZCuts.h"

#include "TrkEventPrimitives/VertexType.h"

#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"

const float WZBackgroudTriggerStudy::PI = 3.1415;

WZBackgroudTriggerStudy::WZBackgroudTriggerStudy(const std::string& name, ISvcLocator* pSvcLocator):
   AthAlgorithm(name, pSvcLocator),
   m_storeGate("StoreGateSvc", name),
   m_eventInfo(0),
   m_lvl1RoIs(0),
   m_l2Electrons(0),
   m_efElectrons(0),
   m_offlineElectrons(0),
   m_offlineClusters(0),
   m_l2Photons(0),
   m_efPhotons(0),
   m_offlinePhotons(0),
   m_primaryVertex(0),
   m_offlineJets(0),
   m_offlineMet(0),
   m_lvl1RoIsLocation("LVL1_ROI"),
   m_l2ElectronsLocation("HLT_L2ElectronFex"),
   m_efElectronsLocation("HLT_egamma_Electrons"),
   m_offlineElectronsLocation("ElectronAODCollection"),
   m_offlineClustersLocation("egClusterCollection"),
   m_l2PhotonsLocation("HLT_L2PhotonFex"),
   m_efPhotonsLocation("HLT_egamma_Photons"),
   m_offlinePhotonsLocation("PhotonAODCollection"),
   m_PrimaryVertexLocation("VxPrimaryCandidate"),
   m_offlineMetLocation("MET_RefFinal"),//("MET_LocHadTopo"),
   m_trigger("Trig::TrigDecisionTool/TrigDecisionTool"),
   m_trigMatch("TrigMatchTool/TrigMatchTool")
{
   
   declareProperty("offlineJetsCollection",m_offlineJetsLocation = "AntiKt4TopoJets");//("AntiKt4H1TopoJets"),
   declareProperty("offlineMETCollection",m_offlineMetLocation = "MET_RefFinal");//("MET_LocHadTopo");
   
   declareProperty("missingEtCut",m_missingEtCut = 25.);
   
   m_histoSvc = 0;
   m_histos = 0;
   m_cuts = 0;
   m_histoNames = 0;
   
   m_eventsPassing_e20l_2j10 = 0;
   m_eventsPassing_e20l_3j10 = 0;
   m_eventsPassing_e20l_4j10 = 0;
}

WZBackgroudTriggerStudy::~WZBackgroudTriggerStudy(void){
   
}

StatusCode WZBackgroudTriggerStudy::initialize(void){
   
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   *m_log << MSG::INFO << "Initializing..." << endreq;
   
   // Load all the tools, TrigDecisionTool, TrigMatchTool, HistoSvc
   StatusCode sc = LoadTools();
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "Failed to load tools." << endreq;
      return sc;
   }
   
   // pass histogramming service to HistogramManager
   m_histos = new WZHistos(m_histoSvc);
   m_histoNames = new WZHistoList;
   
   m_cuts = new WZCuts;
   
   m_s_e20_loose = "e20_loose";
   m_s_e20_looseTrk = "e20_looseTrk";
   m_s_e20_loose1 = "e20_loose1";
   m_s_e20_loose_2j10_a4tc_EFFS = "e20_loose_2j10_a4tc_EFFS";
   m_s_e20_loose_3j10_a4tc_EFFS = "e20_loose_3j10_a4tc_EFFS";
   m_s_e20_loose_4j10_a4tc_EFFS = "e20_loose_4j10_a4tc_EFFS";
   
   
   return sc;
}

StatusCode WZBackgroudTriggerStudy::LoadTools(void){
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   StatusCode sc;
   
   sc = m_trigger.retrieve();
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "Failed to retrieve TrigDecisionTool." << endreq;
      return sc;
   }
   
   sc = m_trigMatch.retrieve();
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "Failed to retrieve TrigMatchTool." << endreq;
      return sc;
   }
   
   // Load Histogramming Service
   sc = service("THistSvc",m_histoSvc);
   if(sc.isFailure()){
      *m_log << MSG::ERROR <<"Failed to retrieve Histo Service"<<endreq;
      return sc;
   }
   
   return sc;
}

StatusCode WZBackgroudTriggerStudy::execute(void){
   
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   // create status code for general use
   StatusCode sc;
   
   // load store gate objects
   sc = LoadContainers();
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[execute] Failed to load containers." << endreq;
      return sc;
   }
   
   
   // check for minimum vertices and tracks
   if(!m_cuts->HasMinimumVertex(m_primaryVertex)){
      *m_log << MSG::DEBUG << "[execute] Failed Vertex+Tracks cut." << endreq;
      return sc;
   }
   
   const double missEt = m_offlineMet->et()/GeV;
   
   sc = m_histos->FillTH1(m_histoNames->missingEt,missEt);
   if (sc.isFailure()){
      *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->missingEt << endreq;
      return sc;
   }
   
   if(m_trigger->isPassed(m_s_e20_loose_2j10_a4tc_EFFS)){
      sc = m_histos->FillTH1(m_histoNames->missingEt_e20_loose_2j10_a4tc_EFFS,missEt);
      if (sc.isFailure()){
         *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->missingEt_e20_loose_2j10_a4tc_EFFS << endreq;
         return sc;
      }
      *m_log << MSG::DEBUG << "[execute] Event passed: " << m_s_e20_loose_2j10_a4tc_EFFS << endreq;
   }
   
   if(m_trigger->isPassed(m_s_e20_loose_3j10_a4tc_EFFS)){
      sc = m_histos->FillTH1(m_histoNames->missingEt_e20_loose_3j10_a4tc_EFFS,missEt);
      if (sc.isFailure()){
         *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->missingEt_e20_loose_3j10_a4tc_EFFS << endreq;
         return sc;
      }
      *m_log << MSG::DEBUG << "[execute] Event passed: " << m_s_e20_loose_3j10_a4tc_EFFS << endreq;
   }
   
   if(m_trigger->isPassed(m_s_e20_loose_4j10_a4tc_EFFS)){
      sc = m_histos->FillTH1(m_histoNames->missingEt_e20_loose_4j10_a4tc_EFFS,missEt);
      if (sc.isFailure()){
         *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->missingEt_e20_loose_4j10_a4tc_EFFS << endreq;
         return sc;
      }
      *m_log << MSG::DEBUG << "[execute] Event passed: " << m_s_e20_loose_4j10_a4tc_EFFS << endreq;
   }
   
//    const unsigned int runNumber = m_eventInfo->event_ID()->run_number();
//    const unsigned short int lumiblockNumber =m_eventInfo->event_ID()->lumi_block();
   
//    *m_log << MSG::INFO << "[execute] Missing ET source: " << m_offlineMet->getSource() << endreq;
//    *m_log << MSG::INFO << "[execute] Missing ET etx: " << m_offlineMet->etx() << endreq;
//    *m_log << MSG::INFO << "[execute] Missing ET ety: " << m_offlineMet->ety() << endreq;
//    *m_log << MSG::INFO << "[execute] Missing ET sumet: " << m_offlineMet->sumet() << endreq;
//    *m_log << MSG::INFO << "[execute] Missing ET et: " << m_offlineMet->et() << endreq;
//    *m_log << MSG::INFO << "[execute] Missing ET phi: " << m_offlineMet->phi() << endreq;
   
   // MET cut
//    if(m_offlineMet->et()/GeV < m_missingEtCut){
//       *m_log << MSG::DEBUG << "[execute] Failed MET cut of " << m_missingEtCut << " GeV " << endreq;
//       return sc;
//    }
//    else
//       m_eventsPassing_met++;
   
   
   
   for(unsigned int electroni = 0;electroni < m_offlineElectrons->size();++electroni){
      const Analysis::Electron* e = m_offlineElectrons->at(electroni);
      
      const float et = e->et()/GeV;
      const float eta = e->eta();
      const float phi = e->phi();
      
      const unsigned int isEM = e->isem();
      const unsigned int medium = egammaPID::ElectronMedium;
      const unsigned int tight = egammaPID::ElectronTight;
      const egPID* pid = e->pid();
      
      *m_log << MSG::INFO << "[execute] isEM: " << std::hex << isEM << " - " << !isEM << " - " << pid->isEM(egammaPID::ALL) << " : medium(" << m_cuts->IsTight(e) << ") = " << medium << " tight(" << m_cuts->IsMedium(e) << ") = " << tight << std::dec << endreq;
      
      
      // plots for all electrons
      sc = m_histos->FillTH1_EtaPhiET(m_histoNames->offElectrons_noCuts,eta,phi,et);
      if (sc.isFailure()){
         *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->offElectrons_noCuts << endreq;
         return sc;
      }
      
      // electrons passing e20_loose_2j10_a4tc_EFFS
      if(m_trigMatch->chainPassedByObject<TrigMatch::TrigElectronEF>(e,m_s_e20_loose_2j10_a4tc_EFFS,0.15) ){
         sc = m_histos->FillTH1_EtaPhiET(m_histoNames->offElectrons_e20_loose_2j10_a4tc_EFFS,eta,phi,et);
         if (sc.isFailure()){
            *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->offElectrons_e20_loose_2j10_a4tc_EFFS << endreq;
            return sc;
         }
      }
      
      
      // electrons passing e20_loose_3j10_a4tc_EFFS
      if(m_trigMatch->chainPassedByObject<TrigMatch::TrigElectronEF>(e,m_s_e20_loose_3j10_a4tc_EFFS,0.15) ){
         sc = m_histos->FillTH1_EtaPhiET(m_histoNames->offElectrons_e20_loose_3j10_a4tc_EFFS,eta,phi,et);
         if (sc.isFailure()){
            *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->offElectrons_e20_loose_3j10_a4tc_EFFS << endreq;
            return sc;
         }
      }
      
      // electrons passing e20_loose_4j10_a4tc_EFFS
      if(m_trigMatch->chainPassedByObject<TrigMatch::TrigElectronEF>(e,m_s_e20_loose_4j10_a4tc_EFFS,0.15) ){
         sc = m_histos->FillTH1_EtaPhiET(m_histoNames->offElectrons_e20_loose_4j10_a4tc_EFFS,eta,phi,et);
         if (sc.isFailure()){
            *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->offElectrons_e20_loose_4j10_a4tc_EFFS << endreq;
            return sc;
         }
      }
      
      // fill transverse mass for all electrons and miss ET
      double transverseMass = TransverseMass(e,m_offlineMet);
      sc = m_histos->FillTH1(m_histoNames->transverseMass,transverseMass/GeV);
      if (sc.isFailure()){
         *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->transverseMass << endreq;
         return sc;
      }
      
      
      // Get L1 ROI
//       std::vector<const TrigMatch::TrigElectronL1*> rois = m_trigMatch->matchToTriggerObjects<TrigMatch::TrigElectronL1,Analysis::Electron>(e,m_s_e20_loose_2j10_a4tc_EFFS,0.2);
//       for(unsigned int roii=0;roii<rois.size();++roii){
//          *m_log << MSG::INFO << "[execute] electron roi " << roii << "  " << rois[roii]->eta() << "/" << rois[roii]->phi() << " " << (rois[roii]->pt()/GeV) << endreq;
//       }
      
   }// end for(electronItr)
   
   
   unsigned short leadingJeti = m_offlineJets->size();
   float leadingJetEt = 0.;
   unsigned short nextToLeadingJeti = m_offlineJets->size();
   float nextToLeadingJetEt = 0.;
   /// Loop over Jets
   for(unsigned int jeti=0;jeti<m_offlineJets->size();++jeti){
      
      Jet const *  jet = m_offlineJets->at(jeti);
      
      double EMJES = jet->getMoment("EMJES");
      
      Jet::hlv_t emjesJet = EMJES*jet->hlv(P4SignalState::JETEMSCALE);
      
      double eta = emjesJet.eta();
      double phi = emjesJet.phi();
      double et  = emjesJet.et()/GeV;
      
      // All jets
      std::string hname = m_histoNames->offJets_noCuts;
      sc = m_histos->FillTH1_EtaPhiET(hname,eta,phi,et);
      if (sc.isFailure()){
         *m_log << MSG::ERROR << "[execute] Failed to fill: " << hname << endreq;
         return sc;
      }
      
      // Check if this jet is overlapping with an electron
      if(!IsIsolated(emjesJet,m_offlineElectrons,0.5)){
         *m_log << MSG::DEBUG << "[execute] Jet overlaps Electron." << endreq;
         continue;
      }
      
      // jets passing e20_loose_2j10_a4tc_EFFS
      if(m_trigMatch->chainPassedByObject<TrigMatch::TrigJetEF>(jet,m_s_e20_loose_2j10_a4tc_EFFS,0.15) ){
         hname = m_histoNames->offElectrons_e20_loose_2j10_a4tc_EFFS;
         sc = m_histos->FillTH1_EtaPhiET(hname,eta,phi,et);
         if (sc.isFailure()){
            *m_log << MSG::ERROR << "[execute] Failed to fill: " << hname << endreq;
            return sc;
         }
      }
      
      // jets passing e20_loose_3j10_a4tc_EFFS
      if(m_trigMatch->chainPassedByObject<TrigMatch::TrigJetEF>(jet,m_s_e20_loose_3j10_a4tc_EFFS,0.15) ){
         hname = m_histoNames->offElectrons_e20_loose_3j10_a4tc_EFFS;
         sc = m_histos->FillTH1_EtaPhiET(hname,eta,phi,et);
         if (sc.isFailure()){
            *m_log << MSG::ERROR << "[execute] Failed to fill: " << hname << endreq;
            return sc;
         }
      }
      
      // jets passing e20_loose_4j10_a4tc_EFFS
      if(m_trigMatch->chainPassedByObject<TrigMatch::TrigJetEF>(jet,m_s_e20_loose_4j10_a4tc_EFFS,0.15) ){
         hname = m_histoNames->offElectrons_e20_loose_4j10_a4tc_EFFS;
         sc = m_histos->FillTH1_EtaPhiET(hname,eta,phi,et);
         if (sc.isFailure()){
            *m_log << MSG::ERROR << "[execute] Failed to fill: " << hname << endreq;
            return sc;
         }
      }
      
      
      // Get L1 ROI
//       std::vector<const TrigMatch::TrigJetL1*> rois = m_trigMatch->matchToTriggerObjects<TrigMatch::TrigJetL1,Jet>(jet,m_s_e20_loose_2j10_a4tc_EFFS,0.5);
//       for(unsigned int roii=0;roii<rois.size();++roii){
//          *m_log << MSG::INFO << "[execute] jet roi " << roii << "  " << rois[roii]->eta() << "/" << rois[roii]->phi() << " " << (rois[roii]->pt()/GeV) << endreq;
//       }
      
      
      
      // E_T cut of 20 GeV
      //if(et < 20.) continue;
      
      // Isolated from electrons
      //if(!IsIsolated(emjesJet,m_offlineElectrons)) continue;
      
      
      if(et > leadingJetEt){
         nextToLeadingJeti = leadingJeti;
         nextToLeadingJetEt = leadingJetEt;
         
         leadingJeti = jeti;
         leadingJetEt = et;
      }
      
   }// end for(jeti)
   
   // find overlapping electrons and jets for EF_e20_loose_2j10_a4tc_EFFS
   //std::map<unsigned short int,unsigned short int>* list = FindOverlappingElectronsAndJets(e_passing_EF_e20_loose_2j10_a4tc_EFFS,jet_passing_EF_e20_loose_2j10_a4tc_EFFS,0.2);
   
   // plot the lead jet and next to lead jet et/eta/phi
   if(leadingJeti != m_offlineJets->size()){
      Jet const *  jet = m_offlineJets->at(leadingJeti);
      sc = m_histos->FillTH1_EtaPhiET(m_histoNames->offJets_jet1,jet->eta(),jet->phi(),leadingJetEt);
      if (sc.isFailure()){
         *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->offJets_jet1 << endreq;
         return sc;
      }
   }
   
   if(nextToLeadingJeti != m_offlineJets->size()){
      Jet const *  jet = m_offlineJets->at(nextToLeadingJeti);
      sc = m_histos->FillTH1_EtaPhiET(m_histoNames->offJets_jet2,jet->eta(),jet->phi(),nextToLeadingJetEt);
      if (sc.isFailure()){
         *m_log << MSG::ERROR << "[execute] Failed to fill: " << m_histoNames->offJets_jet2 << endreq;
         return sc;
      }
   }
   
   
   
//    const Trig::FeatureContainer featureCont = m_trigger->features(m_s_e20_loose_2j10_a4tc_EFFS);
//    std::vector<Trig::Feature<Jet> > EFjets = featureCont.get<Jet>();
//    *m_log << MSG::INFO << "[execute] Trigger Jets passing " << m_s_e20_loose_2j10_a4tc_EFFS << endreq;
//    for(unsigned int jeti=0;jeti<EFjets.size();++jeti){
//       const Jet* jet = EFjets[jeti].cptr();
//       *m_log << MSG::INFO << "[execute]   jet2 " << jeti << "  " << jet->eta() << "/" << jet->phi() << " " << jet->et() << endreq;
//
//    }
   
   
          
   
   
   return sc;
}

// return map<electronContainerIndex,jetContainerIndex> that reports which
// electrons and jets are within a radius dr_min of one another and therefore
// considered overlapping
std::map<unsigned short int,unsigned short int>* WZBackgroudTriggerStudy::FindOverlappingElectronsAndJets(std::vector<unsigned short int>& electron,std::vector<unsigned short int>& jet,double dr_min){
   
   std::map<unsigned short int,unsigned short int>* list = new std::map<unsigned short int,unsigned short int>;
   
   for(unsigned int electroni=0;electroni<electron.size();++electroni){
      unsigned short int eContainerIndex = electron[electroni];
      Analysis::Electron const * e = m_offlineElectrons->at(eContainerIndex);
      
      double r_e = radius<Analysis::Electron>(e);
      
      for(unsigned int jeti=0;jeti<jet.size();++jeti){
         unsigned short int jetContainerIndex = jet[jeti];
         Jet const *  jet = m_offlineJets->at(jetContainerIndex);
         
         double r_j = radius<Jet>(jet);
         
         double dr = fabs(r_e - r_j);
         
         if(dr < dr_min){
            (*list)[eContainerIndex] = jetContainerIndex;
         }
         
         
      }// end for(jeti)
      
   }// end for(electroni)
   
   return list;
}


StatusCode WZBackgroudTriggerStudy::LoadContainers(void){
   StatusCode sc;
   
   sc = m_storeGate->retrieve(m_eventInfo);
   if(sc.isFailure()){msg(MSG::INFO)<<"Failed to load EventInfo"<<endreq;return sc;}
   
   sc = m_storeGate->retrieve(m_l2Electrons,m_l2ElectronsLocation);
   if(sc.isFailure()){msg(MSG::INFO)<<"Failed to load L2 Electrons"<<endreq;return sc;}
   
   sc = m_storeGate->retrieve(m_efElectrons,m_efElectronsLocation);
   if(sc.isFailure()){msg(MSG::INFO)<<"Failed to load EF Electrons"<<endreq;return sc;}
   
   sc = m_storeGate->retrieve(m_offlineElectrons,m_offlineElectronsLocation);
   if(sc.isFailure()){msg(MSG::INFO)<<"Failed to load Offline Electrons"<<endreq;return sc;}
   
   sc = m_storeGate->retrieve(m_offlineClusters,m_offlineClustersLocation);
   if(sc.isFailure()){msg(MSG::INFO)<<"Failed to load Offline Clusters"<<endreq;return sc;}
   
   sc = m_storeGate->retrieve(m_primaryVertex,m_PrimaryVertexLocation);
   if(sc.isFailure()){msg(MSG::INFO)<<"Failed to load Primary Vertex"<<endreq;return sc;}
   
   sc = m_storeGate->retrieve(m_offlineJets,m_offlineJetsLocation);
   if(sc.isFailure()){msg(MSG::INFO)<<"Failed to load: " << m_offlineJetsLocation <<endreq;return sc;}
   
   sc = m_storeGate->retrieve(m_offlineMet,m_offlineMetLocation);
   if(sc.isFailure()){msg(MSG::INFO)<<"Failed to load: " << m_offlineMetLocation <<endreq;return sc;}
   
   return sc;
}

StatusCode WZBackgroudTriggerStudy::finalize(void){
   
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   
   (*m_log) << MSG::INFO << " Number of events Passing EF_e20_loose_2j10_a4tc_EFFS: " << m_eventsPassing_e20l_2j10 << endreq;
   (*m_log) << MSG::INFO << " Number of events Passing EF_e20_loose_3j10_a4tc_EFFS: " << m_eventsPassing_e20l_3j10 << endreq;
   (*m_log) << MSG::INFO << " Number of events Passing EF_e20_loose_4j10_a4tc_EFFS: " << m_eventsPassing_e20l_4j10 << endreq;
   
   delete m_cuts;
   m_cuts = 0;
   delete m_histoNames;
   m_histoNames = 0;
   
   
   return StatusCode::SUCCESS;
}

float WZBackgroudTriggerStudy::GetInvariantMass(Analysis::Electron *e1,Analysis::Electron *e2){
   TLorentzVector v1,v2;
   v1.SetPxPyPzE(e1->px(),e1->py(),e1->pz(),e1->e());
   v2.SetPxPyPzE(e2->px(),e2->py(),e2->pz(),e2->e());
   
   double m_inv = (v1+v2).M();
   
   return m_inv;
}

const TrigMatch::TrigElectronL2* WZBackgroudTriggerStudy::GetMatchedL2Electron(Analysis::Electron *electron,std::string l2chain,float radius)
{
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   
   // get vector of matched L2 electrons
   std::vector<const TrigMatch::TrigElectronL2*> trigElectrons = m_trigMatch->matchToTriggerObjects<TrigMatch::TrigElectronL2>(electron,l2chain,radius);
   
   if(trigElectrons.size() == 0){
      *m_log << MSG::WARNING << "vector has no entries" << endreq;
      return (TrigMatch::TrigElectronL2*)0;
   }
   
   if(trigElectrons.size() == 1){
      // if there is only one match, use it
      return trigElectrons[0];
   }
   
   // if there are more than one, take the one with closest cluster energy
   const TrigMatch::TrigElectronL2 *selectedTrigElectron = 0;
   float minDeltaET = 99999999.;
   for(unsigned int i=0;i<trigElectrons.size();++i){
      float deltaET = fabs(electron->cluster()->et() - trigElectrons[i]->cluster()->et());
      if(deltaET < minDeltaET){
         minDeltaET = deltaET;
         selectedTrigElectron = trigElectrons[i];
      }
   }
   
   if(selectedTrigElectron != 0){
      return selectedTrigElectron;
      *m_log << MSG::INFO << " Matched TrigElectron deltaET: " << minDeltaET << endreq;
   }
   
   *m_log << MSG::INFO << " No Matched TrigElectron" << endreq;
   return (TrigMatch::TrigElectronL2*)0;
   
}


const TrigMatch::TrigElectronEF* WZBackgroudTriggerStudy::GetMatchedEFElectron(Analysis::Electron *electron,std::string EFchain,float radius)
{
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   // get vector of matched EF electrons
   std::vector<const TrigMatch::TrigElectronEF*> trigElectrons = m_trigMatch->matchToTriggerObjects<TrigMatch::TrigElectronEF>(electron,EFchain,radius);
   
   if(trigElectrons.size() == 0){
      *m_log << MSG::WARNING << "vector has no entries" << endreq;
      return (TrigMatch::TrigElectronEF*)0;
   }
   
   if(trigElectrons.size() == 1){
      // if there is only one match, use it
      return trigElectrons[0];
   }
   
   // if there are more than one, take the one with closest cluster energy
   const TrigMatch::TrigElectronEF *selectedTrigElectron = 0;
   float minDeltaET = 99999999.;
   for(unsigned int i=0;i<trigElectrons.size();++i){
      float deltaET = fabs(electron->cluster()->et() - trigElectrons[i]->cluster()->et());
      if(deltaET < minDeltaET){
         minDeltaET = deltaET;
         selectedTrigElectron = trigElectrons[i];
      }
   }
   
   if(selectedTrigElectron != 0){
      return selectedTrigElectron;
      *m_log << MSG::INFO << " Matched TrigElectron deltaET: " << minDeltaET << endreq;
   }
   
   *m_log << MSG::INFO << " No Matched TrigElectron" << endreq;
   return (TrigMatch::TrigElectronEF*)0;
   
}

bool WZBackgroudTriggerStudy::IsIsolated(Jet::hlv_t& emjesJet,const ElectronContainer* electrons, const unsigned int dr){
   
   for(unsigned int e=0;e<electrons->size();++e){
      const Analysis::Electron* electron = electrons->at(e);
      
      float r_el  = sqrt(electron->eta()*electron->eta() + electron->phi()*electron->phi());
      float r_jet = sqrt(emjesJet.eta()*emjesJet.eta()   + emjesJet.phi()*emjesJet.phi());
      
      if(fabs(r_el - r_jet) < dr)
         return false;
   }
   
   return true;
}

// calculate the transverse mass for electron and missing E_T
double WZBackgroudTriggerStudy::TransverseMass(Analysis::Electron const * electron,MissingET const *met){
   double m_transverse = -1.;
   
   double dPhi = fabs(electron->phi() - met->phi());
   
   if(met != 0 && electron != 0)
      m_transverse = 2.*met->et()*electron->et() * ( 1 - cos(dPhi) );
   
   return m_transverse;
}

