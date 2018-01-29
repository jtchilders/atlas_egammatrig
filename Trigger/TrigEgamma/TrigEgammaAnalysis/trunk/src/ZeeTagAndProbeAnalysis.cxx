
#include "TrigEgammaAnalysis/ZeeTagAndProbeAnalysis.h"
#include "TrigEgammaAnalysis/ElectronList.h"
#include "TrigEgammaAnalysis/ElectronCuts.h"
#include "TrigEgammaAnalysis/EfficiencyPlot.h"
#include "TrigEgammaAnalysis/L2vsOfflineElectronPlots.h"
#include "TrigEgammaAnalysis/TrigElectronPlots.h"

#include "TrkEventPrimitives/VertexType.h"

#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"

TrigEgammaZeeTagAndProbeAnalysis::TrigEgammaZeeTagAndProbeAnalysis(const std::string& name, ISvcLocator* pSvcLocator):
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
   m_trigMatch("TrigMatchTool/TrigMatchTool"),
   m_nProbes(0),
   m_nProbes_L2_e20_loose(0),
   m_nProbes_EF_e20_loose(0),
   m_nTags(0)
{
   
}

TrigEgammaZeeTagAndProbeAnalysis::~TrigEgammaZeeTagAndProbeAnalysis(void){
   
}

StatusCode TrigEgammaZeeTagAndProbeAnalysis::initialize(void){
   
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
   
   /////////////////////////////////////////////////////////
   // Tag and Probe Cuts 
   /////////////////////////////////////////////////////////
   
   m_tagCuts = new ElectronCuts;
   m_tagCuts->DoPtCut(false);
   m_tagCuts->DoTrackPtCut(false);
   m_tagCuts->DoSiHitsCut(false);
   m_tagCuts->DoPixHitsCut(false);
   m_tagCuts->DoTrtHitsCut(false);
   m_tagCuts->DoBlayerHitsCut(false);
   m_tagCuts->RequireTight(false);
   m_tagCuts->RequireMedium(false);
   m_tagCuts->RequireLoose(true);
   m_tagList = new ElectronList(m_tagCuts);
   
   m_probeCuts = new ElectronCuts;
   m_probeCuts->DoPtCut(false);
   m_probeCuts->DoTrackPtCut(false);
   m_probeCuts->DoSiHitsCut(false);
   m_probeCuts->DoPixHitsCut(false);
   m_probeCuts->DoTrtHitsCut(false);
   m_probeCuts->DoBlayerHitsCut(false);
   m_probeCuts->RequireTight(false);
   m_probeCuts->RequireMedium(false);
   m_probeCuts->RequireLoose(false);
   m_probeList = new ElectronList(m_probeCuts);
   
   
   
   
   
   
   return sc;
}

void TrigEgammaZeeTagAndProbeAnalysis::ZeroContainerPointers(void){
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

StatusCode TrigEgammaZeeTagAndProbeAnalysis::LoadTools(void){
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

StatusCode TrigEgammaZeeTagAndProbeAnalysis::BookHistos(void){
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   StatusCode sc;
   
   std::string outputBaseDir = "/AANT/";
   
   ///////////
   // TrigElectron plots
   std::string str_trigElectron = outputBaseDir + "TrigElectronTrack_L2_e20_loose/";
   m_trigE_probe_L2_e20_loose = new TrigElectronPlots;
   m_trigE_probe_L2_e20_loose->SetColor(kRed);
   sc = m_trigE_probe_L2_e20_loose->RegisterHistograms(m_histoSvc,str_trigElectron);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register TrigElectronPlots to directory: " << str_trigElectron << endreq;
      return sc;
   }
   
   str_trigElectron = outputBaseDir + "TrigElectronTrack_L2_e20_loose_Zee/";
   m_trigE_probe_L2_e20_loose_Zee = new TrigElectronPlots;
   m_trigE_probe_L2_e20_loose_Zee->SetColor(kRed);
   sc = m_trigE_probe_L2_e20_loose_Zee->RegisterHistograms(m_histoSvc,str_trigElectron);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register TrigElectronPlots to directory: " << str_trigElectron << endreq;
      return sc;
   }
   
   //////////////////////////////////
   // L2 vs Offline plots
   std::string str_L2vsOffDir = outputBaseDir + "L2vsOff_L2_e20_loose/";
   m_l2vsOff_probe_L2_e20_loose = new L2vsOfflineElectronPlots;
   m_l2vsOff_probe_L2_e20_loose->SetColor(kRed);
   sc = m_l2vsOff_probe_L2_e20_loose->RegisterHistograms(m_histoSvc,str_L2vsOffDir);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register TrigElectronPlots to directory: " << str_L2vsOffDir << endreq;
      return sc;
   }
   
   str_L2vsOffDir = outputBaseDir + "L2vsOff_L2_e20_loose_Zee/";
   m_l2vsOff_probe_L2_e20_loose_Zee = new L2vsOfflineElectronPlots;
   m_l2vsOff_probe_L2_e20_loose_Zee->SetColor(kRed);
   sc = m_l2vsOff_probe_L2_e20_loose_Zee->RegisterHistograms(m_histoSvc,str_L2vsOffDir);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register TrigElectronPlots to directory: " << str_L2vsOffDir << endreq;
      return sc;
   }
   
   ///////////////////////////////////////
   // 2D Eta/Phi map of offline electron
   // eta/phi where no L2 electron was
   // matched to offline electron
   str_L2vsOffDir = outputBaseDir + "OfflineWithoutL2/";
   m_h2f_probe_noL2e_etaPhi = new TH2F("h2f_probe_noL2e_etaPhi",";#eta;#phi",50,-2.5,2.5,64,0,2*3.14159265);
   std::string regName = str_L2vsOffDir + m_h2f_probe_noL2e_etaPhi->GetName();
   sc = m_histoSvc->regHist(regName,m_h2f_probe_noL2e_etaPhi);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h2f_probe_noL2e_etaPhi->GetName() << " to directory: " << str_L2vsOffDir << endreq;
      return sc;
   }
   
   m_h1f_probe_noL2e_et = new TH1F("h1f_probe_noL2e_et",";E [GeV]",500,0,500);
   regName = str_L2vsOffDir + m_h1f_probe_noL2e_et->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_probe_noL2e_et);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_probe_noL2e_et->GetName() << " to directory: " << str_L2vsOffDir << endreq;
      return sc;
   }
   
   
   ///////////
   // Invariant Mass Zee
   
   m_h1f_inv_mass_ee = new TH1F("h1f_inv_mass_ee","M_{ee};M_{ee} (Gev);# electrons",500,0,500);
   regName = outputBaseDir + m_h1f_inv_mass_ee->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_inv_mass_ee);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_inv_mass_ee->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   /////////
   // Tag Plots
   
   m_h1f_tag_et = new TH1F("h1f_tag_et","Tag Electron Transverse Energy; E_{T}(Gev);# tag electrons",200,0,200);
   regName = outputBaseDir + m_h1f_tag_et->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_tag_et);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_tag_et->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   m_h1f_tag_eta = new TH1F("h1f_tag_eta","Tag Electron #eta; #eta;# tag electrons",50,-2.5,2.5);
   regName = outputBaseDir + m_h1f_tag_eta->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_tag_eta);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_tag_eta->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   m_h1f_tag_phi = new TH1F("h1f_tag_phi","Tag Electron #phi; #phi;# tag electrons",64,-3.145,3.145);
   regName = outputBaseDir + m_h1f_tag_phi->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_tag_phi);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_tag_phi->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   m_h1f_tag_etcone30 = new TH1F("h1f_tag_etcone30","Tag Electron E_{T}^{cone30}; E_{T}^{cone30};# tag electrons",25,-5,20);
   regName = outputBaseDir + m_h1f_tag_etcone30->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_tag_etcone30);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_tag_etcone30->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   /////////
   // Probe Plots
   
   m_h1f_probe_et = new TH1F("h1f_probe_et","Probe Electron Transverse Energy; E_{T}(Gev);# probe electrons",200,0,200);
   regName = outputBaseDir + m_h1f_probe_et->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_probe_et);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_probe_et->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   m_h1f_probe_eta = new TH1F("h1f_probe_eta","Probe Electron #eta; #eta;# probe electrons",50,-2.5,2.5);
   regName = outputBaseDir + m_h1f_probe_eta->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_probe_eta);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_probe_eta->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   m_h1f_probe_phi = new TH1F("h1f_probe_phi","Probe Electron #phi; #phi;# probe electrons",64,-3.145,3.145);
   regName = outputBaseDir + m_h1f_probe_phi->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_probe_phi);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_probe_phi->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   m_h1f_probe_etcone30 = new TH1F("h1f_probe_etcone30","Probe Electron E_{T}^{cone30}; E_{T}^{cone30};# probe electrons",25,-5,20);
   regName = outputBaseDir + m_h1f_probe_etcone30->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_probe_etcone30);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_probe_etcone30->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   //////////
   // Probes that are from the primary vertex
   m_h1f_probe_et_privx = new TH1F("h1f_probe_et_privx","Probe Electrons Transverse Energy from Primary Vertices; E_{T};# probe electrons",200,0,200);
   regName = outputBaseDir + m_h1f_probe_et_privx->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_probe_et_privx);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_probe_et_privx->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   //////////
   // Probes passing EF_e20_loose
   
   m_h1f_probe_et_EF_e20_loose = new TH1F("h1f_probe_et_EF_e20_loose","E_{T} for probes passing EF_e20_loose; E_{T} (Gev);# probe electrons",200,0,200);
   regName = outputBaseDir + m_h1f_probe_et_EF_e20_loose->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_probe_et_EF_e20_loose);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_probe_et_EF_e20_loose->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   // AND from Primary Vertex
   m_h1f_probe_et_privx_EF_e20_loose = new TH1F("h1f_probe_et_privx_EF_e20_loose","Probe Electrons Transverse Energy from Primary Vertices passing EF_e20_loose; E_{T};# probe electrons",200,0,200);
   regName = outputBaseDir + m_h1f_probe_et_privx_EF_e20_loose->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_probe_et_privx_EF_e20_loose);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_probe_et_privx_EF_e20_loose->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   //////////
   // Probes passing L2 and EF e20_loose
   
   m_h1f_probe_et_L2_e20_loose = new TH1F("h1f_probe_et_L2_e20_loose","E_{T} for probes passing L2_e20_loose; E_{T} (Gev);# probe electrons",200,0,200);
   regName = outputBaseDir + m_h1f_probe_et_L2_e20_loose->GetName();
   sc = m_histoSvc->regHist(regName,m_h1f_probe_et_L2_e20_loose);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_h1f_probe_et_L2_e20_loose->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   
   //////////////////////////////
   // Create Efficiency plots
   
   std::string baseEffDir = outputBaseDir + "efficiencies/";
   
   // L2_e20_loose
   m_eff_L2_e20_loose = new EfficiencyPlot("eff_L2_e20_loose",";E_{T}[GeV];Efficiency",100,0,100);
   sc = m_eff_L2_e20_loose->Register(m_histoSvc,baseEffDir);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register efficiency plot for eff_L2_e20_loose to directory: " << baseEffDir << endreq;
      return sc;
   }
   
   // EF_e20_loose
   m_eff_EF_e20_loose = new EfficiencyPlot("eff_EF_e20_loose",";E_{T}[GeV];Efficiency",100,0,100);
   sc = m_eff_EF_e20_loose->Register(m_histoSvc,baseEffDir);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register efficiency plot for eff_EF_e20_loose to directory: " << baseEffDir << endreq;
      return sc;
   }
   
   return sc;
}

StatusCode TrigEgammaZeeTagAndProbeAnalysis::execute(void){
   
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
   
   // fill the list of tag electrons
   if(!m_tagList->FillList(m_offlineElectrons,m_trigMatch,"EF_e20_loose")){
      // if there are no tag electrons move on to next event
      m_tagList->clear();
      
      *m_log << MSG::INFO << "No Tags to process." << endreq;
      return sc;
   }
   
   // loop over tag electrons to find probes
   if(!m_probeList->FillList(m_offlineElectrons,m_trigMatch,"")){
      // if there are no probe electrons move on to next event
      m_probeList->clear();
      m_tagList->clear();
      
      *m_log << MSG::INFO << "No Probes to process." << endreq;
      return sc;
   }
   else if(m_probeList->size() == 1){
      // make sure if there is only one probe it is not the tag
      if(m_tagList->size() == 1){
         if(m_probeList->at(0) == m_tagList->at(0)){
            m_probeList->clear();
            m_tagList->clear();
            return sc;
         }
      }
   }
   
      
   for(unsigned int i=0;i<m_tagList->size();++i){
      Analysis::Electron *tag = m_tagList->at(i);
      
      *m_log << MSG::INFO << "Number of Tag Electrons: " << m_tagList->size() << endreq;
      
      // tag distributions
      m_h1f_tag_et->Fill(tag->et()/GeV);
      m_h1f_tag_eta->Fill(tag->eta());
      m_h1f_tag_phi->Fill(tag->phi());
      
      // increment number of Tag electrons
      m_nTags++;
      
      // loop over the probe electron and fill plots
      for(unsigned int j=0;j<m_probeList->size();++j){
         Analysis::Electron *probe = m_probeList->at(j);
         
         *m_log << MSG::INFO << "Number of Probe Electrons: " << m_probeList->size() << endreq;
         
         //  skip tag
         if(tag == probe) continue;
         
         // plot the invariant mass for all combinations
         float invmass = GetInvariantMass(tag,probe)/GeV;
         if(invmass > 0.0001)
            m_h1f_inv_mass_ee->Fill(invmass);
         
         // probe distributions
         m_h1f_probe_eta->Fill(probe->eta());
         m_h1f_probe_phi->Fill(probe->phi());
         m_h1f_probe_et->Fill(probe->et()/GeV);
         
         // count the number of probe electrons
         m_nProbes++;
         
         // count electrons from a primary vertex
         if(probe->trackParticle()->reconstructedVertex()->vertexType() == Trk::PriVtx){
            m_h1f_probe_et_privx->Fill(probe->et()/GeV);
            
         }
         
         // look at electrons who fall into the Z mass peak
         //if(80 <= invmass && invmass <= 95){
         
         // Also see if electron passed L2_e20_loose
         if(m_trigMatch->chainPassedByObject<TrigMatch::TrigElectronL2>(probe,"L2_e20_loose",0.15)){
            
            // count the number of probe electrons passing L2_e20_loose
            m_nProbes_L2_e20_loose++;
            
            m_h1f_probe_et_L2_e20_loose->Fill(probe->et()/GeV);
            
            m_eff_L2_e20_loose->FillDenominator(probe->et()/GeV);
            
            
            const TrigMatch::TrigElectronL2 *l2electronMatch = GetMatchedL2Electron(probe,"L2_e20_loose",0.15);
            // if matched electron was found
            if(l2electronMatch != 0){
               if(80 <= invmass && invmass <= 95){
                  m_trigE_probe_L2_e20_loose_Zee->Fill(l2electronMatch);
                  m_l2vsOff_probe_L2_e20_loose_Zee->Fill(l2electronMatch,probe);
                  m_eff_L2_e20_loose->FillNumerator(probe->et()/GeV);
               }
               else{
                  m_trigE_probe_L2_e20_loose->Fill(l2electronMatch);
                  m_l2vsOff_probe_L2_e20_loose->Fill(l2electronMatch,probe);
               }
            }
            // if no matched electron was found
            else{
               *m_log << MSG::INFO << "No matching L2 electron Found." << endreq;
               
               // fill eta/phi for offline electron with a matched L2 electron
               m_h2f_probe_noL2e_etaPhi->Fill(probe->eta(),probe->phi());
               m_h1f_probe_noL2e_et->Fill(probe->e()/GeV);
            }
            
            
            if(m_trigMatch->chainPassedByObject<TrigMatch::TrigElectronL2>(probe,"EF_e20_loose",0.15)){
               m_eff_EF_e20_loose->FillDenominator(probe->et()/GeV);
               
               const TrigMatch::TrigElectronEF *EFelectronMatch = GetMatchedEFElectron(probe,"EF_e20_loose",0.15);
               // if matched electron was found
               if(EFelectronMatch != 0){
                  if(80 <= invmass && invmass <= 95){
                     m_eff_EF_e20_loose->FillNumerator(probe->et()/GeV);
                  }
               }
               
            }// end if(EF_e20_loose)
            
         }// end if(L2_e20_loose)
         
         probe = 0;
      }// end for(probe)
      
      tag = 0;
      
   }// end for(tags)
   
   
   m_tagList->clear();
   m_probeList->clear();
   
   return sc;
}



StatusCode TrigEgammaZeeTagAndProbeAnalysis::LoadContainers(void){
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

StatusCode TrigEgammaZeeTagAndProbeAnalysis::finalize(void){
   
   // setup msg stream for output
   m_log = new MsgStream(msgSvc(), name());
   
   *m_log << MSG::INFO << "////////////////////////////////////////////" << endreq;
   *m_log << MSG::INFO << "///// Particle Count:                      " << endreq;
   *m_log << MSG::INFO << "///// nTags: " << m_nTags << endreq;
   *m_log << MSG::INFO << "///// nProbes: " << m_nProbes << endreq;
   *m_log << MSG::INFO << "///// nProbes_L2_e20_loose: " << m_nProbes_L2_e20_loose << endreq;
   *m_log << MSG::INFO << "///// nProbes_EF_e20_loose: " << m_nProbes_EF_e20_loose << endreq;
   *m_log << MSG::INFO << "////////////////////////////////////////////" << endreq;
   
   
   return StatusCode::SUCCESS;
}


bool TrigEgammaZeeTagAndProbeAnalysis::HasMinimumVertices(void) const{
   
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

float TrigEgammaZeeTagAndProbeAnalysis::GetInvariantMass(Analysis::Electron *e1,Analysis::Electron *e2){
   TLorentzVector v1,v2;
   v1.SetPxPyPzE(e1->px(),e1->py(),e1->pz(),e1->e());
   v2.SetPxPyPzE(e2->px(),e2->py(),e2->pz(),e2->e());
   
   double m_inv = (v1+v2).M();
   
   return m_inv;
}

const TrigMatch::TrigElectronL2* TrigEgammaZeeTagAndProbeAnalysis::GetMatchedL2Electron(Analysis::Electron *electron,std::string l2chain,float radius)
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


const TrigMatch::TrigElectronEF* TrigEgammaZeeTagAndProbeAnalysis::GetMatchedEFElectron(Analysis::Electron *electron,std::string EFchain,float radius)
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


