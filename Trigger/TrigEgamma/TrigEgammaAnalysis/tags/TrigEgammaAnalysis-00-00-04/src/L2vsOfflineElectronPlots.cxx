#include "TrigEgammaAnalysis/L2vsOfflineElectronPlots.h"

#include "AthenaKernel/MsgStreamMember.h"
#include "GaudiKernel/StatusCode.h"

#include "TrigInDetEvent/TrigInDetTrack.h"
#include "TrigInDetEvent/TrigInDetTrackFitPar.h"

#include "Particle/TrackParticle.h"
#include "TrkTrackSummary/TrackSummary.h"
#include "TrkParticleBase/TrackParticleBase.h"
#include "TrkTrack/Track.h"
#include "TrkParameters/Perigee.h"

const float L2vsOfflineElectronPlots::PI = 3.14159265;

L2vsOfflineElectronPlots::L2vsOfflineElectronPlots(void) 
{
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"L2vsOfflineElectronPlots");
   m_color = kBlack;
   
   m_TrigElectronDir = "TrigElectron";
   m_trackDir = "track";
   
   
   
   m_h1f_diff_nSctHits = 0;
   m_h1f_diff_nPixHits = 0;
   m_h1f_diff_nTrtHits = 0;
   m_h1f_diff_nTrtHiHits = 0;
   
   m_h1f_diff_nSctHitsOutlier = 0;
   m_h1f_diff_nPixHitsOutlier = 0;
   m_h1f_diff_nTrtHitsOutlier = 0;
   m_h1f_diff_nTrtHiHitsOutlier = 0;
   
   
   m_h1f_diff_eta = 0;
   m_h1f_diff_phi = 0;
   
   m_h1f_diff_pt = 0;
   m_h1f_diff_et = 0;
   
   m_h1f_diff_track_pt = 0;
   
   m_h1f_diff_z0 = 0;
   m_h1f_diff_a0 = 0;
   m_h1f_diff_phi0 = 0;
   
}

L2vsOfflineElectronPlots::~L2vsOfflineElectronPlots(void)
{
   delete m_log;
   m_log = 0;
}


StatusCode L2vsOfflineElectronPlots::RegisterHistograms(ITHistSvc *histSvc,const std::string dir)
{
   
   if(dir.size() > 0)
      m_TrigElectronDir = dir;
   
   
   std::string regDir = m_TrigElectronDir;
   
   // General 1D histograms
   
   
   // TH1F track histograms
   //regDir = m_TrigElectronDir + '/' + m_trackDir;
   
   
   m_h1f_diff_nSctHits = RegisterTH1F(histSvc,regDir,"h1f_diff_nSctHits",";#Delta N_{SCT} (l2-offline)",100,-50,50);
   if(m_h1f_diff_nSctHits == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_nSctHits->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_nPixHits = RegisterTH1F(histSvc,regDir,"h1f_diff_nPixHits",";#Delta N_{Pix} (l2-offline)",100,-50,50);
   if(m_h1f_diff_nPixHits == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_nPixHits->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   
   m_h1f_diff_nTrtHits = RegisterTH1F(histSvc,regDir,"h1f_diff_nTrtHits",";#Delta N_{TRTHits} (l2-offline)",200,-100,100);
   if(m_h1f_diff_nTrtHits == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_nTrtHits->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   
   m_h1f_diff_nTrtHiHits = RegisterTH1F(histSvc,regDir,"h1f_diff_nTrtHiHits",";#Delta N_{TRTHighHits} (l2-offline)",200,-100,100);
   if(m_h1f_diff_nTrtHiHits == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_nTrtHiHits->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   
   m_h1f_diff_nSctHitsOutlier = RegisterTH1F(histSvc,regDir,"h1f_diff_nSctHitsOutlier",";#Delta N_{SCT+Outliers} (l2-offline)",100,-50,50);
   if(m_h1f_diff_nSctHitsOutlier == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_nSctHitsOutlier->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_nPixHitsOutlier = RegisterTH1F(histSvc,regDir,"h1f_diff_nPixHitsOutlier",";#Delta N_{Pix+Outliers} (l2-offline)",100,-50,50);
   if(m_h1f_diff_nPixHitsOutlier == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_nPixHitsOutlier->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   
   m_h1f_diff_nTrtHitsOutlier = RegisterTH1F(histSvc,regDir,"h1f_diff_nTrtHitsOutlier",";#Delta N_{TRTHits+Outliers} (l2-offline)",200,-100,100);
   if(m_h1f_diff_nTrtHitsOutlier == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_nTrtHitsOutlier->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   
   m_h1f_diff_nTrtHiHitsOutlier = RegisterTH1F(histSvc,regDir,"h1f_diff_nTrtHiHitsOutlier",";#Delta N_{TRTHighHits+Outliers} (l2-offline)",200,-100,100);
   if(m_h1f_diff_nTrtHiHitsOutlier == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_nTrtHiHitsOutlier->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_eta = RegisterTH1F(histSvc,regDir,"h1f_diff_eta",";#Delta #eta (l2-offline)",1000,-10,10);
   if(m_h1f_diff_eta == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_eta->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_phi = RegisterTH1F(histSvc,regDir,"h1f_diff_phi",";#Delta #phi (l2-offline)",1000,-10,10);
   if(m_h1f_diff_phi == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_phi->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_pt = RegisterTH1F(histSvc,regDir,"h1f_diff_pt",";#Delta p_{T} (l2-offline)",2000,-20000,30000);
   if(m_h1f_diff_pt == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_pt->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_et = RegisterTH1F(histSvc,regDir,"h1f_diff_et",";#Delta E_{T} (l2-offline)",2000,-20000,30000);
   if(m_h1f_diff_et == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_et->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_track_pt = RegisterTH1F(histSvc,regDir,"h1f_diff_track_pt",";#Delta p^{trk}_{T} (l2-offline)",2000,-30000,20000);
   if(m_h1f_diff_track_pt == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_track_pt->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_z0 = RegisterTH1F(histSvc,regDir,"h1f_diff_z0",";#Delta z_{0} (l2-offline)",1000,-150,150);
   if(m_h1f_diff_z0 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_z0->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_a0 = RegisterTH1F(histSvc,regDir,"h1f_diff_a0",";#Delta a_{0} (l2-offline)",1000,-150,150);
   if(m_h1f_diff_a0 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_a0->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   m_h1f_diff_phi0 = RegisterTH1F(histSvc,regDir,"h1f_diff_phi0",";#Delta #phi_{0} (l2-offline)",2000,-10,10);
   if(m_h1f_diff_phi0 == 0){
      *m_log << MSG::ERROR << "RegisterHistograms: Could not register " << m_h1f_diff_phi0->GetName() << endreq;
      return StatusCode::FAILURE;
   }
   
   
   // set the color for the histograms
   m_h1f_diff_nSctHits->SetLineColor(m_color);
   m_h1f_diff_nPixHits->SetLineColor(m_color);
   m_h1f_diff_nTrtHits->SetLineColor(m_color);
   m_h1f_diff_nTrtHiHits->SetLineColor(m_color);
   
   m_h1f_diff_nSctHitsOutlier->SetLineColor(m_color);
   m_h1f_diff_nPixHitsOutlier->SetLineColor(m_color);
   m_h1f_diff_nTrtHitsOutlier->SetLineColor(m_color);
   m_h1f_diff_nTrtHiHitsOutlier->SetLineColor(m_color);
   
   
   m_h1f_diff_eta->SetLineColor(m_color);
   m_h1f_diff_phi->SetLineColor(m_color);
   
   m_h1f_diff_pt->SetLineColor(m_color);
   m_h1f_diff_et->SetLineColor(m_color);
   
   m_h1f_diff_track_pt->SetLineColor(m_color);
   
   m_h1f_diff_z0->SetLineColor(m_color);
   m_h1f_diff_a0->SetLineColor(m_color);
   m_h1f_diff_phi0->SetLineColor(m_color);
   
   
   return StatusCode::SUCCESS;
}

TH1F* L2vsOfflineElectronPlots::RegisterTH1F(ITHistSvc *histSvc,std::string dir,
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

TH2F* L2vsOfflineElectronPlots::RegisterTH2F(ITHistSvc *histSvc,std::string dir,
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


void L2vsOfflineElectronPlots::Fill(TrigMatch::TrigElectronL2 const * const l2Electron,Analysis::Electron const * const offElectron){
   
   if(l2Electron == 0 || offElectron == 0){
      *m_log << MSG::WARNING << "Fill: electron pointers empty: l2electron: " << l2Electron << " offElectron: " << offElectron << endreq;
      return;
   }
   
   // get l2 track
   TrigInDetTrack const * const l2track = l2Electron->track();
   
   const int l2PixHits = l2track->NPixelSpacePoints();
   const int l2SctHits = l2track->NSCT_SpacePoints();
   const int l2TrtHits = l2track->NStrawHits();
   const int l2TrtHiHits = l2track->NTRHits();
   
   const float l2eta = l2Electron->eta();
   const float l2phi = l2Electron->phi();
   
   const float l2pt = l2Electron->pt();
   const float l2et = l2Electron->et();
   
   const TrigInDetTrackFitPar *l2trackFitPar = l2track->param();
   
   const float l2trackPt = l2trackFitPar->pT();
   const float l2trackA0 = l2trackFitPar->a0();
   const float l2trackZ0 = l2trackFitPar->z0();
   const float l2trackPhi0 = l2trackFitPar->phi0();
   
   // get off track
   Rec::TrackParticle const * const offTrackParticle = offElectron->trackParticle();
   Trk::TrackSummary const * const offTrackSummary = offTrackParticle->trackSummary();
   Trk::Track const * const offTrack = offTrackParticle->originalTrack();
   Trk::Perigee const * const offPerigee = offTrack->perigeeParameters();
   Trk::MeasuredPerigee const * const offMPerigee = dynamic_cast<Trk::MeasuredPerigee const * const>(offPerigee);
   
   if(offMPerigee == 0){
      *m_log << MSG::INFO << "[Fill] No offline perigee." << endreq;
   }
   
   
   int offPixHits = offTrackSummary->get(Trk::numberOfPixelHits);
   int offPixHitsOutlier = offTrackSummary->get(Trk::numberOfPixelOutliers);
   int offSctHits = offTrackSummary->get(Trk::numberOfSCTHits);
   int offSctHitsOutlier = offTrackSummary->get(Trk::numberOfSCTOutliers);
   int offTrtHits = offTrackSummary->get(Trk::numberOfTRTHits);
   int offTrtHitsOutlier = offTrackSummary->get(Trk::numberOfTRTOutliers);
   int offTrtHiHits = offTrackSummary->get(Trk::numberOfTRTHighThresholdHits);
   int offTrtHiHitsOutlier = offTrackSummary->get(Trk::numberOfTRTHighThresholdOutliers);
   
   float offEta = offElectron->eta();
   float offPhi = offElectron->phi();
   
   float offPt = offElectron->pt();
   float offEt = offElectron->et();
   
   float offTrackPt = -9999999;
   float offTrackA0 = -9999999;
   float offTrackZ0 = -9999999;
   float offTrackPhi0 = -9999999;
   float offTrackEta = -9999999;
   if(offMPerigee != 0){
      offTrackPt = offMPerigee->pT();
      offTrackEta = offMPerigee->eta();
      
      HepVector offPerigeeParams = offMPerigee->parameters();
      offTrackA0 = offPerigeeParams[Trk::d0];
      offTrackZ0 = offPerigeeParams[Trk::z0];
      offTrackPhi0 = offPerigeeParams[Trk::phi0];
   }
   
   
   // fill histograms
   
   m_h1f_diff_nPixHits->Fill(l2PixHits-offPixHits);
   m_h1f_diff_nSctHits->Fill(l2SctHits-offSctHits);
   m_h1f_diff_nTrtHits->Fill(l2TrtHits-offTrtHits);
   m_h1f_diff_nTrtHiHits->Fill(l2TrtHiHits-offTrtHiHits);
   
   m_h1f_diff_nPixHitsOutlier->Fill(l2PixHits-(offPixHits+offPixHitsOutlier));
   m_h1f_diff_nSctHitsOutlier->Fill(l2SctHits-(offSctHits+offSctHitsOutlier));
   m_h1f_diff_nTrtHitsOutlier->Fill(l2TrtHits-(offTrtHits+offTrtHitsOutlier));
   m_h1f_diff_nTrtHiHitsOutlier->Fill(l2TrtHiHits-(offTrtHiHits+offTrtHiHitsOutlier));
   
   m_h1f_diff_eta->Fill(l2eta-offEta);
   const float dphi = l2phi - offPhi;
   if(dphi > PI)
      m_h1f_diff_phi->Fill(dphi-2.*PI);
   else if(dphi < -PI)
      m_h1f_diff_phi->Fill(dphi+2.*PI);
   else
      m_h1f_diff_phi->Fill(l2phi-offPhi);
   
   m_h1f_diff_pt->Fill(l2pt-offPt);
   m_h1f_diff_et->Fill(l2et-offEt);
   
   m_h1f_diff_track_pt->Fill(l2trackPt-offTrackPt);
   
   m_h1f_diff_z0->Fill(l2trackZ0-offTrackZ0);
   m_h1f_diff_a0->Fill(l2trackA0-offTrackA0);
   m_h1f_diff_phi0->Fill(l2trackPhi0-offTrackPhi0);
   
   
}


