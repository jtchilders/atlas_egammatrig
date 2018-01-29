
#include "TrigEgammaAnalysis/TRTAnalysis.h"

#include "TrigEgammaAnalysis/RateHistory.h"

TrigEgammaTRTAnalysis::TrigEgammaTRTAnalysis(const std::string& name, ISvcLocator* pSvcLocator):
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
   
}

TrigEgammaTRTAnalysis::~TrigEgammaTRTAnalysis(void){
   
}

StatusCode TrigEgammaTRTAnalysis::initialize(void){
   
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
   
   // Book Histograms
   sc = BookHistos();
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "Failed to book histograms." << endreq;
      return sc;
   }
   
   return sc;
}

void TrigEgammaTRTAnalysis::ZeroContainerPointers(void){
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

StatusCode TrigEgammaTRTAnalysis::LoadTools(void){
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

StatusCode TrigEgammaTRTAnalysis::BookHistos(void){
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   StatusCode sc;
   
   std::string outputDir = "/AANT/rateHistories";   
   
   rh_EF_e15_medium_TRT = new RateHistory("rh_EF_e15_medium_TRT","EF_e15_medium_TRT;Lumi-block;Rate[Hz]");
   sc = rh_EF_e15_medium_TRT->Register(m_histoSvc,outputDir);
   if(sc.isFailure()){
      *m_log << MSG::WARNING << "Failed to register histogram: " << rh_EF_e15_medium_TRT->GetName() << endreq;
   }
   
   rh_EF_e15_medium = new RateHistory("rh_EF_e15_medium","EF_e15_medium;Lumi-block;Rate[Hz]");
   sc = rh_EF_e15_medium->Register(m_histoSvc,outputDir);
   if(sc.isFailure()){
      *m_log << MSG::WARNING << "Failed to register histogram: " << rh_EF_e15_medium->GetName() << endreq;
   }
   
   rh_L2_e15_medium_TRT = new RateHistory("rh_L2_e15_medium_TRT","L2_e15_medium_TRT;Lumi-block;Rate[Hz]");
   sc = rh_L2_e15_medium_TRT->Register(m_histoSvc,outputDir);
   if(sc.isFailure()){
      *m_log << MSG::WARNING << "Failed to register histogram: " << rh_L2_e15_medium_TRT->GetName() << endreq;
   }
   
   rh_L2_e15_medium = new RateHistory("rh_L2_e15_medium","L2_e15_medium;Lumi-block;Rate[Hz]");
   sc = rh_L2_e15_medium->Register(m_histoSvc,outputDir);
   if(sc.isFailure()){
      *m_log << MSG::WARNING << "Failed to register histogram: " << rh_L2_e15_medium->GetName() << endreq;
   }
   
   return sc;
}

StatusCode TrigEgammaTRTAnalysis::execute(void){
   
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
   const unsigned short int lumiblockNumber =m_eventInfo->event_ID()->lumi_block();
   
   
   // Fill Rate Histories
   if(m_trigger->isPassed("L2_e15_medium")){
      float prescale = m_trigger->getPrescale("L2_e15_medium");
      rh_L2_e15_medium->Fill(lumiblockNumber,prescale);
   }
   if(m_trigger->isPassed("L2_e15_medium_TRT")){
      float prescale = m_trigger->getPrescale("L2_e15_medium_TRT");
      rh_L2_e15_medium_TRT->Fill(lumiblockNumber,prescale);
   }
   if(m_trigger->isPassed("EF_e15_medium")){
      float prescale = m_trigger->getPrescale("EF_e15_medium");
      rh_EF_e15_medium->Fill(lumiblockNumber,prescale);
   }
   if(m_trigger->isPassed("EF_e15_medium_TRT")){
      float prescale = m_trigger->getPrescale("EF_e15_medium_TRT");
      rh_EF_e15_medium_TRT->Fill(lumiblockNumber,prescale);
   }
   
   *m_log << MSG::INFO << "exiting execute." << endreq;
   
   return sc;
}



StatusCode TrigEgammaTRTAnalysis::LoadContainers(void){
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

StatusCode TrigEgammaTRTAnalysis::finalize(void){
   
   rh_EF_e15_medium_TRT->BuildHisto();
   rh_EF_e15_medium->BuildHisto();
   rh_L2_e15_medium_TRT->BuildHisto();
   rh_L2_e15_medium->BuildHisto();
   
   
   
   return StatusCode::SUCCESS;
}






