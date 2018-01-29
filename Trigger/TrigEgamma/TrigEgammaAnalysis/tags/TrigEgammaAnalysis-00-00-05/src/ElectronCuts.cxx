#include "TrigEgammaAnalysis/ElectronCuts.h"

#include "TrkTrackSummary/TrackSummary.h"

ElectronCuts::ElectronCuts(void):
   m_doAuthorCut(true),
   m_author(egammaParameters::AuthorElectron | egammaParameters::AuthorSofte),
   m_doEtaCut(true),
   m_etaMax(2.47),
   m_doCrackCut(true),
   m_crackEtaMin(1.37),
   m_crackEtaMax(1.52),
   m_doOqCut(true),
   m_oqMask(egammaPID::BADCLUSELECTRON),
   m_doPtCut(true),
   m_pTcut(20.), // GeV
   m_doTrackPtCut(true),
   m_track_pTcut(2.), // GeV
   m_doSiHitsCut(true),
   m_siHits(7),
   m_doPixHitsCut(true),
   m_pixHits(1),
   m_doTrtHitsCut(true),
   m_trtHits(10),
   m_doBlayerHitsCut(true),
   m_bLayerHits(1),
   m_doLoose(false),
   m_doMedium(false),
   m_doTight(false)
{
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"ElectronCuts");
}

ElectronCuts::~ElectronCuts(void)
{
   delete m_log;
   m_log = 0;
}

bool ElectronCuts::IsGoodElectron(Analysis::Electron const * const e) const
{
   
   if(m_doAuthorCut)     if(!IsElectronAuthor(e))       return false;
   if(m_doEtaCut)        if(!IsInEtaAcceptance(e))      return false;
   if(m_doCrackCut)      if(!IsNotInCrackRegion(e))     return false;
   if(m_doOqCut)         if(!IsGoodObjectQuality(e))    return false;
   if(m_doPtCut)         if(!PassesPtCut(e))            return false;
   if(m_doTrackPtCut)    if(!PassesTrackPtCut(e))       return false;
   if(m_doSiHitsCut)     if(!PassesMinSiHitsCut(e))     return false;
   if(m_doPixHitsCut)    if(!PassesMinPixHitsCut(e))    return false;
   if(m_doTrtHitsCut)    if(!PassesMinTRTHitsCut(e))    return false;
   if(m_doBlayerHitsCut) if(!PassesMinBLayerHitsCut(e)) return false;
   
   if(m_doLoose)         if(!IsLoose(e))                return false;
   if(m_doMedium)        if(!IsMedium(e))               return false;
   if(m_doTight)         if(!IsTight(e))                return false;
   
   return true;
}

bool ElectronCuts::IsElectronAuthor(Analysis::Electron const * const e) const 
{
   if(m_author & e->author())
      return true;
   
   *m_log << MSG::INFO << "Failed IsElectronAuthor." << endreq;
   return false;
}

bool ElectronCuts::IsInEtaAcceptance(Analysis::Electron const * const e) const 
{
   if(fabs(e->eta()) < m_etaMax)
      return true;
   
   *m_log << MSG::INFO << "Failed IsInEtaAcceptance." << endreq;
   return false;
}

bool ElectronCuts::IsNotInCrackRegion(Analysis::Electron const * const e) const 
{
   const float feta = fabs(e->eta());
   if(!(m_crackEtaMin < feta && feta < m_crackEtaMax))
      return true;
   
   *m_log << MSG::INFO << "Failed IsNotInCrackRegion." << endreq;
   return false;
}

bool ElectronCuts::IsGoodObjectQuality(Analysis::Electron const * const e) const
{
   if(!e->isgoodoq(m_oqMask))
      return true;
   
   *m_log << MSG::INFO << "Failed IsGoodObjectQuality." << endreq;
   return false;
}

bool ElectronCuts::PassesPtCut(Analysis::Electron const * const e) const
{
   float electronPtGeV = e->pt()/GeV;
   if(electronPtGeV > m_pTcut)
      return true;
   
   *m_log << MSG::INFO << "Failed PtCut." << endreq;
   return false;
}

bool ElectronCuts::PassesTrackPtCut(Analysis::Electron const * const e) const
{
   float electronPtGeV = e->trackParticle()->pt()/GeV;
   if(electronPtGeV > m_track_pTcut)
      return true;
   
   *m_log << MSG::INFO << "Failed TrackPtCut." << endreq;
   return false;
}

bool ElectronCuts::PassesMinSiHitsCut(Analysis::Electron const * const e) const
{
   const Trk::TrackSummary *sum = e->trackParticle()->trackSummary();
   
   if(sum->get(Trk::numberOfSCTHits) >= m_siHits)
      return true;
   
   *m_log << MSG::INFO << "Failed SiHits." << endreq;
   return false;
}

bool ElectronCuts::PassesMinPixHitsCut(Analysis::Electron const * const e) const
{
   const Trk::TrackSummary *sum = e->trackParticle()->trackSummary();
   
   if(sum->get(Trk::numberOfPixelHits) >= m_pixHits)
      return true;
   
   *m_log << MSG::INFO << "Failed PixHits." << endreq;
   return false;
}

bool ElectronCuts::PassesMinTRTHitsCut(Analysis::Electron const * const e) const
{
   const Trk::TrackSummary *sum = e->trackParticle()->trackSummary();
   
   if((sum->get(Trk::numberOfTRTHits)+sum->get(Trk::numberOfTRTOutliers)) >= m_trtHits)
      return true;
   
   *m_log << MSG::INFO << "Failed TRTHits." << endreq;
   return false;
}

bool ElectronCuts::PassesMinBLayerHitsCut(Analysis::Electron const * const e) const
{
   const Trk::TrackSummary *sum = e->trackParticle()->trackSummary();
   
   if(sum->get(Trk::expectBLayerHit) && sum->get(Trk::numberOfBLayerHits) >= m_bLayerHits)
      return true;
   
   *m_log << MSG::INFO << "Failed bLayerHits." << endreq;
   return false;
}

bool ElectronCuts::IsTight(Analysis::Electron const * const e) const
{
   return e->isElectron(egammaPID::ElectronTight);
}

bool ElectronCuts::IsMedium(Analysis::Electron const * const e) const
{
   return e->isElectron(egammaPID::ElectronMedium);
}

bool ElectronCuts::IsLoose(Analysis::Electron const * const e) const
{
   return e->isElectron(egammaPID::ElectronLoose);
}

