
#include "TrigEgammaAnalysis/WZBckgrdTrigStudy.h"
#include "TrigEgammaAnalysis/ElectronList.h"
#include "TrigEgammaAnalysis/ElectronCuts.h"
#include "TrigEgammaAnalysis/EfficiencyPlot.h"
#include "TrigEgammaAnalysis/L2vsOfflineElectronPlots.h"
#include "TrigEgammaAnalysis/TrigElectronPlots.h"
#include "TrigEgammaAnalysis/HistogramManager.h"

#include "TrkEventPrimitives/VertexType.h"

#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"

WZBackgroudTriggerStudy::WZBackgroudTriggerStudy(const std::string& name, ISvcLocator* pSvcLocator):
   AthAlgorithm(name, pSvcLocator),
   m_storeGate("StoreGateSvc", name),
   m_lvl1RoIsLocation("LVL1_ROI"),
   m_l2ElectronsLocation("HLT_L2ElectronFex"),
   m_efElectronsLocation("HLT_egamma_Electrons"),
   m_offlineElectronsLocation("ElectronAODCollection"),
   m_offlineClustersLocation("egClusterCollection"),
   m_l2PhotonsLocation("HLT_L2PhotonFex"),
   m_efPhotonsLocation("HLT_egamma_Photons"),
   m_offlinePhotonsLocation("PhotonAODCollection"),
   m_PrimaryVertexLocation("VxPrimaryCandidate"),
   m_trigger("Trig::TrigDecisionTool/TrigDecisionTool"),
   m_trigMatch("TrigMatchTool/TrigMatchTool")
{
   m_histoMan = 0;
   
   m_s_e20_loose = "e20_loose";
   m_s_e20_loose_dir = m_s_e20_loose + "/";
   m_s_e20l_offlineElectronET = "e20l_offlineElectron_ET";
   
   m_s_e20_looseTrk = "e20_looseTrk";
   m_s_e20_looseTrk_dir = m_s_e20_looseTrk + "/";
   m_s_e20lTrk_offlineElectronET = "e20lTrk_offlineElectron_ET";
   
   m_s_e20_loose1 = "e20_loose1";
   m_s_e20_loose1_dir = m_s_e20_loose1 + "/";
   m_s_e20l1_offlineElectronET = "e20l1_offlineElectron_ET";
   
}

WZBackgroudTriggerStudy::~WZBackgroudTriggerStudy(void){
   
}

StatusCode WZBackgroudTriggerStudy::initialize(void){
   
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   *m_log << MSG::INFO << "Initializing..." << endreq;
   
   ZeroContainerPointers();
   
   // Load all the tools, TrigDecisionTool, TrigMatchTool, HistoSvc
   StatusCode sc = LoadTools();
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "Failed to load tools." << endreq;
      return sc;
   }
   
   // pass histogramming service to HistogramManager
   m_histoMan = new HistogramManager(m_histoSvc);
   // initialize histograms
   sc = BookHistos();
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "Failed to book histos." << endreq;
      return sc;
   }
   
   return sc;
}

void WZBackgroudTriggerStudy::ZeroContainerPointers(void){
   m_eventInfo        = 0;
   m_lvl1RoIs         = 0;
   m_l2Electrons      = 0;
   m_efElectrons      = 0;
   m_offlineElectrons = 0;
   m_offlineClusters  = 0;
   m_l2Photons        = 0;
   m_efPhotons        = 0;
   m_offlinePhotons   = 0;
   m_primaryVertex    = 0;
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
      *m_log << MSG::ERROR << "Failed to load containers." << endreq;
      return sc;
   }
   
   
//    const unsigned int runNumber = m_eventInfo->event_ID()->run_number();
//    const unsigned short int lumiblockNumber =m_eventInfo->event_ID()->lumi_block();
   
   // check for minimum vertices and tracks
   if(!HasMinimumVertices()){
      *m_log << MSG::INFO << "Failed Vertex+Tracks cut." << endreq;
      return sc;
   }
   
   
   ElectronContainer::const_iterator electronItr = m_offlineElectrons->begin();
   
   for(;electronItr != m_offlineElectrons->end();++electronItr){
      Analysis::Electron* e = (*electronItr);
      
      std::string efChain = "EF_";
      efChain += m_s_e20_loose;
      if(m_trigMatch->chainPassedByObject<TrigMatch::TrigElectronEF>(e,efChain,0.15) ){
         m_histoMan->FillTH1(m_s_e20l_offlineElectronET,e->et()/GeV);
      }
      
      efChain = "EF_";
      efChain += m_s_e20_looseTrk;
      if(m_trigMatch->chainPassedByObject<TrigMatch::TrigElectronEF>(e,efChain,0.15) ){
         m_histoMan->FillTH1(m_s_e20lTrk_offlineElectronET,e->et()/GeV);
      }
      
      efChain = "EF_";
      efChain += m_s_e20_loose1;
      if(m_trigMatch->chainPassedByObject<TrigMatch::TrigElectronEF>(e,efChain,0.15) ){
         m_histoMan->FillTH1(m_s_e20l1_offlineElectronET,e->et()/GeV);
      }
      
   }// end for(electronItr)
   
   
   
   return sc;
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
   
   return sc;
}

StatusCode WZBackgroudTriggerStudy::finalize(void){
   
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   
   return StatusCode::SUCCESS;
}


bool WZBackgroudTriggerStudy::HasMinimumVertices(void) const{
   
   VxContainer::const_iterator itr = m_primaryVertex->begin();
   
   unsigned int numVertices = 0;
   
   // loop over the vertices
   for(;itr != m_primaryVertex->end();++itr){
      
      Trk::VxCandidate *vertex = *itr;
//       msg(MSG::INFO)<<"vertexType: "<<(int)vertex->vertexType()<<endreq;
      if(vertex->vertexType() == Trk::PriVtx){
//          msg(MSG::INFO)<<"number of tracks: "<<vertex->vxTrackAtVertex()->size()<<endreq;
         if(vertex->vxTrackAtVertex()->size() >= m_numTrksAtPrimVertex){
//             msg(MSG::INFO)<<"z: "<<vertex->recVertex().position().z()<<endreq;
            if(fabs(vertex->recVertex().position().z()) < m_vertexPosition){
               numVertices++;
            }// if(within vertex position cut)
         }// if(number of tracks at vertex)
         
      }// if(primary vertex)
      
   }// end for(vertices)
//    msg(MSG::INFO)<<"number of vertices: "<<numVertices<<endreq;
   if(numVertices >= m_numPrimaryVertex)
      return true;
   
   return false;
   
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


StatusCode WZBackgroudTriggerStudy::BookHistos(void)
{
   StatusCode sc;
   
   std::string oneD = "1D/";
   std::string directory,name;
   
   int nbinX = 500;
   float xmin = 0.;
   float xmax = 500.;
   
   directory = m_s_e20_loose_dir + oneD;
   name = m_s_e20l_offlineElectronET;
   sc = m_histoMan->AddTH1F(directory,name,"electrons passing e20_loose;offline electron E_{T} [GeV]",nbinX,xmin,xmax);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[BookHistos] Failed to book histo " << name << " to directory " << directory << endreq;
      return sc;
   }
   
   
   directory = m_s_e20_looseTrk_dir + oneD;
   name = m_s_e20lTrk_offlineElectronET;
   sc = m_histoMan->AddTH1F(directory,name,"electrons passing e20_looseTrk;offline electron E_{T} [GeV]",nbinX,xmin,xmax);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[BookHistos] Failed to book histo " << name << " to directory " << directory << endreq;
      return sc;
   }
   
   directory = m_s_e20_loose1_dir + oneD;
   name = m_s_e20l1_offlineElectronET;
   sc = m_histoMan->AddTH1F(directory,name,"electrons passing e20_loose1;offline electron E_{T} [GeV]",nbinX,xmin,xmax);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[BookHistos] Failed to book histo " << name << " to directory " << directory << endreq;
      return sc;
   }
   
   return sc;
}

