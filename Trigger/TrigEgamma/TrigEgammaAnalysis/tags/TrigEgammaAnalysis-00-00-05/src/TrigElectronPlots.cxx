#include "TrigEgammaAnalysis/TrigElectronPlots.h"

#include "AthenaKernel/MsgStreamMember.h"
#include "GaudiKernel/StatusCode.h"

#include "TrigInDetEvent/TrigInDetTrack.h"
#include "TrigInDetEvent/TrigInDetTrackFitPar.h"

TrigElectronPlots::TrigElectronPlots(void) 
{
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"TrigElectronPlots");
   m_color = kBlack;
   
   m_TrigElectronDir = "TrigElectron";
   m_trackDir = "track";
   
   
   m_h1f_charge = 0;
   
   m_h1f_track_NPixelSpacePoints = 0;
   m_h1f_track_NSctSpacePoints = 0;
   m_h1f_track_hitPattern = 0;
   
   m_h1f_track_nTrtStrawHits = 0;
   m_h1f_track_nTrtStraw = 0;
   m_h1f_track_nTrtStrawTime = 0;
   m_h1f_track_nTrtHighThresholdHits = 0;
   
   m_h1f_track_trtHitsRatio = 0;
   
   m_h1f_track_chi2 = 0;
   
   m_h1f_track_a0 = 0;
   m_h1f_track_ea0 = 0;
   m_h1f_track_z0 = 0;
   m_h1f_track_ez0 = 0;
   m_h1f_track_phi0 = 0;
   m_h1f_track_ephi0 = 0;
   m_h1f_track_eta = 0;
   m_h1f_track_eeta = 0;
   m_h1f_track_pt = 0;
   m_h1f_track_ept = 0;
   
   m_h1f_trkEtaAtCalo = 0;
   m_h1f_trkPhiAtCalo = 0;
   
   m_h1f_trkClusDeta = 0;
   m_h1f_trkClusDphi = 0;
   m_h1f_deltaEta1 = 0;
   m_h1f_deltaPhi2 = 0;
   
   m_h1f_etOverPt = 0;
   m_h1f_caloEta = 0;
   m_h1f_caloPhi = 0;
   
   m_h1f_rEta = 0;
   m_h1f_eRatio = 0;
   m_h1f_etHad1 = 0;
   
   
   
}

TrigElectronPlots::~TrigElectronPlots(void)
{
   delete m_log;
   m_log = 0;
}


StatusCode TrigElectronPlots::RegisterHistograms(ITHistSvc *histSvc,const std::string dir)
{
   
   if(dir.size() > 0)
      m_TrigElectronDir = dir;
   
   
   std::string regDir = m_TrigElectronDir;
   
   // General 1D histograms
   
   m_h1f_charge = RegisterTH1F(histSvc,regDir,"h1f_charge","",20,-10,10);
   if(m_h1f_charge == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_charge->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   
   // TH1F track histograms
   regDir = m_TrigElectronDir + '/' + m_trackDir;
   
   m_h1f_track_algoId = RegisterTH1F(histSvc,dir,"h1f_track_algoId","",400,-200,200);
   if(m_h1f_track_algoId == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_algoId->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_NPixelSpacePoints = RegisterTH1F(histSvc,dir,"h1f_track_NPixelSpacePoints","",20,0,20);
   if(m_h1f_track_NPixelSpacePoints == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_NPixelSpacePoints->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_NSctSpacePoints = RegisterTH1F(histSvc,dir,"h1f_track_NSctSpacePoints","",20,0,20);
   if(m_h1f_track_NSctSpacePoints == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_NSctSpacePoints->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_hitPattern = RegisterTH1F(histSvc,dir,"h1f_track_hitPattern","",200,0,200);
   if(m_h1f_track_hitPattern == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_hitPattern->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_nTrtStrawHits = RegisterTH1F(histSvc,dir,"h1f_track_nTrtStrawHits","",100,0,100);
   if(m_h1f_track_nTrtStrawHits == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_nTrtStrawHits->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_nTrtStraw = RegisterTH1F(histSvc,dir,"h1f_track_nTrtStraw","",100,0,100);
   if(m_h1f_track_nTrtStraw == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_nTrtStraw->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_nTrtStrawTime = RegisterTH1F(histSvc,dir,"h1f_track_nTrtStrawTime","",100,0,100);
   if(m_h1f_track_nTrtStrawTime == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_nTrtStrawTime->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_nTrtHighThresholdHits = RegisterTH1F(histSvc,dir,"h1f_track_nTrtHighThresholdHits","",100,0,100);
   if(m_h1f_track_nTrtHighThresholdHits == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_nTrtHighThresholdHits->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_trtHitsRatio = RegisterTH1F(histSvc,dir,"h1f_track_trtHitsRatio","",100,0,1);
   if(m_h1f_track_trtHitsRatio == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_trtHitsRatio->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_chi2 = RegisterTH1F(histSvc,dir,"h1f_track_chi2","",500,0,500);
   if(m_h1f_track_chi2 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_chi2->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_a0 = RegisterTH1F(histSvc,dir,"h1f_track_a0","",200,-10,10);
   if(m_h1f_track_a0 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_a0->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_ea0 = RegisterTH1F(histSvc,dir,"h1f_track_ea0","",200,0,5);
   if(m_h1f_track_ea0 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_ea0->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_z0 = RegisterTH1F(histSvc,dir,"h1f_track_z0","",200,-100,100);
   if(m_h1f_track_z0 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_z0->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_ez0 = RegisterTH1F(histSvc,dir,"h1f_track_ez0","",200,0,5);
   if(m_h1f_track_ez0 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_ez0->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_phi0 = RegisterTH1F(histSvc,dir,"h1f_track_phi0","",64,-3.1415,3.1415);
   if(m_h1f_track_phi0 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_phi0->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_ephi0 = RegisterTH1F(histSvc,dir,"h1f_track_ephi0","",100,0,1);
   if(m_h1f_track_ephi0 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_ephi0->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_eta = RegisterTH1F(histSvc,dir,"h1f_track_eta","",50,-2.5,2.5);
   if(m_h1f_track_eta == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_eta->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_eeta = RegisterTH1F(histSvc,dir,"h1f_track_eeta","",100,0,1);
   if(m_h1f_track_eeta == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_eeta->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_pt = RegisterTH1F(histSvc,dir,"h1f_track_pt","",500,0,500);
   if(m_h1f_track_pt == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_pt->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_track_ept = RegisterTH1F(histSvc,dir,"h1f_track_ept","",100,0,50);
   if(m_h1f_track_ept == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_track_ept->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   
   
   m_h1f_trkEtaAtCalo = RegisterTH1F(histSvc,dir,"h1f_trkEtaAtCalo","",50,-2.5,2.5);
   if(m_h1f_trkEtaAtCalo == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_trkEtaAtCalo->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_trkPhiAtCalo = RegisterTH1F(histSvc,dir,"h1f_trkPhiAtCalo","",64,-3.1415,3.1415);
   if(m_h1f_trkPhiAtCalo == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_trkPhiAtCalo->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_trkClusDeta = RegisterTH1F(histSvc,dir,"h1f_trkClusDeta","",100,-1,1);
   if(m_h1f_trkClusDeta == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_trkClusDeta->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_trkClusDphi = RegisterTH1F(histSvc,dir,"h1f_trkClusDphi","",100,-1,1);
   if(m_h1f_trkClusDphi == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_trkClusDphi->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_deltaEta1 = RegisterTH1F(histSvc,dir,"h1f_deltaEta1","",100,-1,1);
   if(m_h1f_deltaEta1 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_deltaEta1->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_deltaPhi2 = RegisterTH1F(histSvc,dir,"h1f_deltaPhi2","",100,-1,1);
   if(m_h1f_deltaPhi2 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_deltaPhi2->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_etOverPt = RegisterTH1F(histSvc,dir,"h1f_etOverPt","",100,0,100);
   if(m_h1f_etOverPt == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_etOverPt->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_caloEta = RegisterTH1F(histSvc,dir,"h1f_caloEta","",50,-2.5,2.5);
   if(m_h1f_caloEta == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_caloEta->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_caloPhi = RegisterTH1F(histSvc,dir,"h1f_caloPhi","",64,-3.1415,3.1415);
   if(m_h1f_caloPhi == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_caloPhi->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_rEta = RegisterTH1F(histSvc,dir,"h1f_rEta","",100,0,1);
   if(m_h1f_rEta == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_rEta->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_eRatio = RegisterTH1F(histSvc,dir,"h1f_eRatio","",100,0,1);
   if(m_h1f_eRatio == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_eRatio->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_etHad1 = RegisterTH1F(histSvc,dir,"h1f_etHad1","",500,0,500);
   if(m_h1f_etHad1 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_etHad1->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   
   
   
   
   // set the color for the histograms
   m_h1f_charge->SetLineColor(m_color);
   
   m_h1f_track_algoId->SetLineColor(m_color);
   m_h1f_track_NPixelSpacePoints->SetLineColor(m_color);
   m_h1f_track_NSctSpacePoints->SetLineColor(m_color);
   m_h1f_track_hitPattern->SetLineColor(m_color);
   
   m_h1f_track_nTrtStrawHits->SetLineColor(m_color);
   m_h1f_track_nTrtStraw->SetLineColor(m_color);
   m_h1f_track_nTrtStrawTime->SetLineColor(m_color);
   m_h1f_track_nTrtHighThresholdHits->SetLineColor(m_color);
   
   m_h1f_track_trtHitsRatio->SetMarkerColor(m_color);
   
   m_h1f_track_chi2->SetLineColor(m_color);
   
   m_h1f_track_a0->SetLineColor(m_color);
   m_h1f_track_ea0->SetLineColor(m_color);
   m_h1f_track_z0->SetLineColor(m_color);
   m_h1f_track_ez0->SetLineColor(m_color);
   m_h1f_track_phi0->SetLineColor(m_color);
   m_h1f_track_ephi0->SetLineColor(m_color);
   m_h1f_track_eta->SetLineColor(m_color);
   m_h1f_track_eeta->SetLineColor(m_color);
   m_h1f_track_pt->SetLineColor(m_color);
   m_h1f_track_ept->SetLineColor(m_color);
   
   m_h1f_trkEtaAtCalo->SetLineColor(m_color);
   m_h1f_trkPhiAtCalo->SetLineColor(m_color);
   
   m_h1f_trkClusDeta->SetLineColor(m_color);
   m_h1f_trkClusDphi->SetLineColor(m_color);
   m_h1f_deltaEta1->SetLineColor(m_color);
   m_h1f_deltaPhi2->SetLineColor(m_color);
   
   m_h1f_etOverPt->SetLineColor(m_color);
   m_h1f_caloEta->SetLineColor(m_color);
   m_h1f_caloPhi->SetLineColor(m_color);
   
   m_h1f_rEta->SetLineColor(m_color);
   m_h1f_eRatio->SetLineColor(m_color);
   m_h1f_etHad1->SetLineColor(m_color);
   
   
   return StatusCode::SUCCESS;
}

TH1F* TrigElectronPlots::RegisterTH1F(ITHistSvc *histSvc,std::string dir,
                                         std::string name,std::string title,
                                         int nbin,float min,float max)
{
   StatusCode sc;
   TH1F *histo = new TH1F(name.c_str(),title.c_str(),nbin,min,max);
   std::string regName = dir + "/" + name;
   sc = histSvc->regHist(regName,histo);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "RegisterTH1F: Could not register " << histo->GetName() << " to directory: " << regName << endreq;
      return (TH1F*)0;
   }
   
   return histo;
}

TH2F* TrigElectronPlots::RegisterTH2F(ITHistSvc *histSvc,std::string dir,
                                         std::string name,std::string title,
                                         int nbinx,float xmin,float xmax,
                                         int nbiny,float ymin,float ymax)
{
   StatusCode sc;
   TH2F *histo = new TH2F(name.c_str(),title.c_str(),nbinx,xmin,xmax,nbiny,ymin,ymax);
   std::string regName = dir + "/" + name;
   sc = histSvc->regHist(regName,histo);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "RegisterTH2F: Could not register " << histo->GetName() << " to directory: " << regName << endreq;
      return (TH2F*)0;
   }
   
   return histo;
}


void TrigElectronPlots::Fill(TrigMatch::TrigElectronL2 const * const electron){
   
   if(electron == 0){
      *m_log << MSG::WARNING << "Fill: electron pointer empty." << endreq;
      return;
   }
   
   if(electron->nTRTHiTHitsRatio() > 0.00005){
      m_h1f_track_trtHitsRatio->Fill(electron->nTRTHiTHitsRatio());
   }
   
   m_h1f_charge->Fill(electron->charge());
   
   const TrigInDetTrack *track = electron->track();
   
   m_h1f_track_NPixelSpacePoints->Fill(track->NPixelSpacePoints());
   m_h1f_track_NSctSpacePoints->Fill(track->NSCT_SpacePoints());
   m_h1f_track_hitPattern->Fill(track->HitPattern());
   
   m_h1f_track_nTrtStrawHits->Fill(track->NStrawHits());
   m_h1f_track_nTrtStraw->Fill(track->NStraw());
   m_h1f_track_nTrtStrawTime->Fill(track->NStrawTime());
   m_h1f_track_nTrtHighThresholdHits->Fill(track->NTRHits());
   
   m_h1f_track_chi2->Fill(track->chi2());
   
   const TrigInDetTrackFitPar *trackFitPar = track->param();
   
   m_h1f_track_a0->Fill(trackFitPar->a0());
   m_h1f_track_ea0->Fill(trackFitPar->ea0());
   m_h1f_track_z0->Fill(trackFitPar->z0());
   m_h1f_track_ez0->Fill(trackFitPar->ez0());
   m_h1f_track_phi0->Fill(trackFitPar->phi0());
   m_h1f_track_ephi0->Fill(trackFitPar->ephi0());
   m_h1f_track_eta->Fill(trackFitPar->eta());
   m_h1f_track_eeta->Fill(trackFitPar->eeta());
   // use fabs since pt for the track is pt*charge
   m_h1f_track_pt->Fill(fabs(trackFitPar->pT()/GeV));
   m_h1f_track_ept->Fill(trackFitPar->epT()/GeV);
   
   m_h1f_trkEtaAtCalo->Fill(electron->trkEtaAtCalo());
   m_h1f_trkPhiAtCalo->Fill(electron->trkPhiAtCalo());
   
   m_h1f_trkClusDeta->Fill(electron->trkClusDeta());
   m_h1f_trkClusDphi->Fill(electron->trkClusDphi());
   m_h1f_deltaEta1->Fill(electron->DeltaEta1());
   m_h1f_deltaPhi2->Fill(electron->DeltaPhi2());
   
   m_h1f_etOverPt->Fill(electron->EtOverPt());
   m_h1f_caloEta->Fill(electron->caloEta());
   m_h1f_caloPhi->Fill(electron->caloPhi());
   
   m_h1f_rEta->Fill(electron->Reta());
   m_h1f_eRatio->Fill(electron->Eratio());
   m_h1f_etHad1->Fill(electron->Ethad1());
   
   
}


