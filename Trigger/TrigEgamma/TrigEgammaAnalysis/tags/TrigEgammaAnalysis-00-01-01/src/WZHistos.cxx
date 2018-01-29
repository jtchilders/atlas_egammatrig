#include "TrigEgammaAnalysis/WZHistos.h"

#include "AthenaKernel/MsgStreamMember.h"
#include "GaudiKernel/StatusCode.h"
#include "GaudiKernel/ITHistSvc.h"


const float WZHistos::PI = 3.1415;

WZHistos::WZHistos(ITHistSvc *histSvc,std::string baseDirectory):
      HistogramManager(histSvc,baseDirectory)
{
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"WZHitos");
   
   histoList = new WZHistoList;
   
   CreateHistos();
}

WZHistos::~WZHistos(void){
   delete m_log;
   m_log = 0;
   
   delete histoList;
   histoList = 0;
}

void WZHistos::CreateHistos(void){
   
   std::string directory,name;
   StatusCode sc;
   
   /// Electron histograms
   
   directory = "electrons";
   
   name = histoList->offElectrons_noCuts;
   sc = AddTH1F_EtaPhiET(name,"all offline electrons (no cuts);offline electron E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->offElectrons_e20_loose_2j10_a4tc_EFFS;
   sc = AddTH1F_EtaPhiET(name,"all offline electrons passing e20_loose_2j10_a4tc_EFFS;offline electron E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->offElectrons_e20_loose_3j10_a4tc_EFFS;
   sc = AddTH1F_EtaPhiET(name,"all offline electrons passing e20_loose_3j10_a4tc_EFFS;offline electron E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->offElectrons_e20_loose_4j10_a4tc_EFFS;
   sc = AddTH1F_EtaPhiET(name,"all offline electrons passing e20_loose_4j10_a4tc_EFFS;offline electron E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   /// Jet Histograms
   
   directory = "jets";
   
   name = histoList->offJets_noCuts;
   sc = AddTH1F_EtaPhiET(name,"all offline jets (no cuts);offline jet E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->offElectrons_e20_loose_2j10_a4tc_EFFS;
   sc = AddTH1F_EtaPhiET(name,"all offline jets passing e20_loose_2j10_a4tc_EFFS;offline jet E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->offElectrons_e20_loose_3j10_a4tc_EFFS;
   sc = AddTH1F_EtaPhiET(name,"all offline jets passing e20_loose_3j10_a4tc_EFFS;offline jet E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->offElectrons_e20_loose_4j10_a4tc_EFFS;
   sc = AddTH1F_EtaPhiET(name,"all offline jets passing e20_loose_4j10_a4tc_EFFS;offline jet E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   /// Leading/Next2Leading Jet
   
   name = histoList->offJets_jet1;
   sc = AddTH1F_EtaPhiET(name,"leading offline jet;offline jet E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->offJets_jet2;
   sc = AddTH1F_EtaPhiET(name,"next to leading offline jet;offline jet E_{T} [GeV]",directory);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   
   /// Missing Et
   
   name = histoList->missingEt;
   sc = AddTH1F(directory,name,"Missing E_{T} for all events;offline jet E_{T} [GeV]",500,0.,500.);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->missingEt_e20_loose_2j10_a4tc_EFFS;
   sc = AddTH1F(directory,name,"Missing E_{T} for events passing e20_loose_2j10_a4tc_EFFS;offline jet E_{T} [GeV]",500,0.,500.);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->missingEt_e20_loose_3j10_a4tc_EFFS;
   sc = AddTH1F(directory,name,"Missing E_{T} for events passing e20_loose_3j10_a4tc_EFFS;offline jet E_{T} [GeV]",500,0.,500.);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   name = histoList->missingEt_e20_loose_4j10_a4tc_EFFS;
   sc = AddTH1F(directory,name,"Missing E_{T} for events passing e20_loose_4j10_a4tc_EFFS;offline jet E_{T} [GeV]",500,0.,500.);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book EtaPhiET histo " << name << " to directory " << directory << endreq;
      return;
   }
   
   
   /// Transverse Mass
   
   directory = "transverseMassPlots";
   name = histoList->transverseMass;
   sc = HistogramManager::AddTH1F(directory,name,"all combinations of electrons and E_{T}^{miss};M_{T} [GeV]",500,0.,1500.);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[CreateHistos] Failed to book histo " << name << " to directory " << directory << endreq;
      return;
   }
   
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
