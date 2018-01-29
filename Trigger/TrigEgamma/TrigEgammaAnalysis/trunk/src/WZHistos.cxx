#include "TrigEgammaAnalysis/WZHistos.h"

#include "AthenaKernel/MsgStreamMember.h"
#include "GaudiKernel/StatusCode.h"
#include "GaudiKernel/ITHistSvc.h"

#include "TAxis.h"
#include "TH1.h"

const float WZHistos::PI = 3.1415;

WZHistos::WZHistos(ITHistSvc *histSvc,std::string baseDirectory):
      HistogramManager(histSvc,baseDirectory)
{
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"WZHitos");
   
   m_histoList = new WZHistoList;
   
   CreateHistos();
}

WZHistos::~WZHistos(void){
   delete m_log;
   m_log = 0;
   
   delete m_histoList;
   m_histoList = 0;
}

void WZHistos::CreateHistos(void){
   
   std::string directory,name;
   StatusCode sc;
   
   /// Electron histograms
   
   AddTH1F_electrons();
   for(unsigned int i=0;i<m_histoList->triggers.size();++i){
      AddTH1F_electrons(m_histoList->triggers[i]);
   }
   
   /// Jet Histograms
   
   AddTH1F_jets();
   for(unsigned int i=0;i<m_histoList->triggers.size();++i){
      AddTH1F_jets(m_histoList->triggers[i]);
   }
   
   
   /// Leading/Next2Leading Jet
   
   directory = "jets";
   
   name = m_histoList->offJets_jet1;
   sc = AddTH1F_EtaPhiET(name,"leading offline jet;offline jet E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = m_histoList->offJets_jet2;
   sc = AddTH1F_EtaPhiET(name,"next to leading offline jet;offline jet E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   
   /// Missing Et
   
   AddTH1F_missingEt();
   for(unsigned int i=0;i<m_histoList->triggers.size();++i){
      AddTH1F_missingEt(m_histoList->triggers[i]);
   }
   
   /// Transverse Mass
   
   directory = "transverseMassPlots";
   
   name = m_histoList->transverseMass;
   sc = HistogramManager::AddTH1F(directory,name,"all combinations of electrons and E_{T}^{miss};M_{T} [GeV]",500,0.,1500.);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   /// Failed Cuts plot
   
   AddTH1F_failedCuts();
   
   
}

void WZHistos::AddTH1F_missingEt(const std::string trigger){
   
   std::string name = m_histoList->missingEt + "_";
   std::string title = "Missing E_{T}";
   if(trigger.size() > 0){
      name += trigger;
      title += " for events passing ";
      title += trigger;
   }
   else{
      name  += "noTrigger";
      title += " for all events";
   }
   
   title += ";offline E_{T}^{miss} [GeV]";
   
   StatusCode sc = AddTH1F("missingEt",name,title,500,0.,500.);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book histo " << name << " to directory missingEt." << endreq;
      return;
   }
   
}

StatusCode WZHistos::FillTH1_missingEt(const std::string trigger,const float missingEt){
   
   std::string name = m_histoList->missingEt + "_" + trigger;
   
   StatusCode sc = FillTH1(name,missingEt);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to fill histo " << name << "." << endreq;
      return sc;
   }
   
   return StatusCode::SUCCESS;
}

void WZHistos::AddTH1F_jets(const std::string trigger){
   
   std::string name = m_histoList->offJets + "_";
   std::string title = "Offline Jets";
   if(trigger.size() > 0){
      name += trigger;
      title += " for events passing ";
      title += trigger;
   }
   else{
      name  += "noTrigger";
      title += " for all events";
   }
   
   title += ";offline jet E_{T} [GeV]";
   
         StatusCode sc = AddTH1F_EtaPhiET(name,title,"jets");
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory jets." << endreq;
      return;
   }
   
}

StatusCode WZHistos::FillTH1_jets(const std::string trigger,const float eta, const float phi, const float et){
   
   std::string name = m_histoList->offJets + "_" + trigger;
   
   StatusCode sc = FillTH1_EtaPhiET(name,eta,phi,et);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to fill EtaPhiET histo " << name << "." << endreq;
      return sc;
   }
   
   return StatusCode::SUCCESS;
}


void WZHistos::AddTH1F_electrons(const std::string trigger){
   
   std::string name = m_histoList->offElectrons + "_";
   std::string title = "Offline Electrons";
   if(trigger.size() > 0){
      name += trigger;
      title += " for events passing ";
      title += trigger;
   }
   else{
      name  += "noTrigger";
      title += " for all events";
   }
   
   title += ";offline electron E_{T} [GeV]";
   
   StatusCode sc = AddTH1F_EtaPhiET(name,title,"electrons");
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory electrons." << endreq;
      return;
   }
   
}

StatusCode WZHistos::FillTH1_electrons(const std::string trigger,const float eta, const float phi, const float et){
   
   std::string name = m_histoList->offElectrons + "_" + trigger;
   
   StatusCode sc = FillTH1_EtaPhiET(name,eta,phi,et);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to fill EtaPhiET histo " << name << "." << endreq;
      return sc;
   }
   
   return StatusCode::SUCCESS;
}


StatusCode WZHistos::AddTH1F_EtaPhiET(
      const std::string name, const std::string title,const std::string directory,
      const unsigned int etaNbins,const float etaMin,const float etaMax,
      const unsigned int phiNbins,const float phiMin,const float phiMax,
      const unsigned int etNbins, const float etMin, const float etMax
                                             )
{
   // create eta plot
   StatusCode sc = AddTH1F(directory,name+"_eta",title+" vs. #eta;#eta",etaNbins,etaMin,etaMax);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[AddTH1F_EtaPhiET] Failed to book histo for eta." << endreq;
      return sc;
   }
   // create phi plot
   sc = AddTH1F(directory,name+"_phi",title+" vs. #phi;#phi",phiNbins,phiMin,phiMax);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[AddTH1F_EtaPhiET] Failed to book histo for phi." << endreq;
      return sc;
   }
   // create ET plot
   sc = AddTH1F(directory,name+"_ET",title+" vs. E_T;E_T",etNbins,etMin,etMax);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[AddTH1F_EtaPhiET] Failed to book histo for E_T." << endreq;
      return sc;
   }
   
   return StatusCode::SUCCESS;
   
}


StatusCode WZHistos::FillTH1_EtaPhiET(const std::string name,
                                              const float etaValue,
                                              const float phiValue,
                                              const float etValue) const
{
   // Fill etaValue
   StatusCode sc = FillTH1(name+"_eta",etaValue);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[FillTH1_EtaPhiET] Failed to fill histogram named: " << (name+"_eta") << endreq;
      return sc;
   }
   // Fill phiValue
   sc = FillTH1(name+"_phi",phiValue);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[FillTH1_EtaPhiET] Failed to fill histogram named: " << (name+"_phi") << endreq;
      return sc;
   }
   // Fill E_T Value
   sc = FillTH1(name+"_ET",etValue);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[FillTH1_EtaPhiET] Failed to fill histogram named: " << (name+"_ET") << endreq;
      return sc;
   }
   
   return StatusCode::SUCCESS;
}

void WZHistos::AddTH1F_failedCuts(void){
   StatusCode sc = HistogramManager::AddTH1F("monitoring",m_histoList->failedCuts,"Failed Cuts",NumberOfCuts,0,NumberOfCuts);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[AddTH1F_failedCuts] Failed to book histo for failed cuts." << endreq;
      return;
   }
   
   TH1* hist = HistogramManager::GetTH1("failedCuts");
   TAxis* axis = hist->GetXaxis();
   axis->SetBinLabel(1,"N_evts");
   axis->SetBinLabel(2,"Vertex");
   axis->SetBinLabel(3,"N_elec");
   axis->SetBinLabel(4,"e_pt");
   axis->SetBinLabel(5,"e_eta");
   axis->SetBinLabel(6,"e_medNotTight");
   axis->SetBinLabel(7,"e_iso");
   axis->SetBinLabel(8,"e_trigger");
}

StatusCode WZHistos::FillTH1_failedCuts(const FAILED_CUTS cut){
   StatusCode sc = HistogramManager::FillTH1(m_histoList->failedCuts,cut);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[FillTH1_failedCus] Failed to fill histogram named: " << m_histoList->failedCuts << endreq;
       return sc;
   }
                  
   return StatusCode::SUCCESS;
}
