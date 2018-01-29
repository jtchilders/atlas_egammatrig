#ifndef ELECTRONCUTS_H
#define ELECTRONCUTS_H

#include <cmath>

#include "GaudiKernel/ITHistSvc.h"
#include "AthenaKernel/MsgStreamMember.h"

#include "Particle/TrackParticle.h" //Reco/Particle

#include "egammaEvent/Electron.h"

class ElectronCuts{
public:
   ElectronCuts(void);
   ~ElectronCuts(void);
   
   // Function to test all enabled cuts (all enabled by default)
   bool IsGoodElectron(Analysis::Electron const * const e) const;
   
   // Functions to turn cuts on/off for IsGoodElectron function
   void DoElectronAuthorCut(const bool value){m_doAuthorCut = value;};
   bool DoElectronAuthorCut(void) const{return m_doAuthorCut;};
   
   void DoEtaAcceptanceCut(const bool value){m_doEtaCut = value;};
   bool DoEtaAcceptanceCut(void) const{return m_doEtaCut;};
   
   void DoCrackExclusionCut(const bool value){m_doCrackCut = value;};
   bool DoCrackExclusionCut(void) const{return m_doCrackCut;};
   
   void DoObjectQualityCut(const bool value){m_doOqCut = value;};
   bool DoObjectQualityCut(void) const{return m_doOqCut;};
   
   void DoPtCut(const bool value){m_doPtCut = value;};
   bool DoPtCut(void) const{return m_doPtCut;};
   
   void DoTrackPtCut(const bool value){m_doTrackPtCut = value;};
   bool DoTrackPtCut(void) const{return m_doTrackPtCut;};
   
   void DoSiHitsCut(const bool value){m_doSiHitsCut = value;};
   bool DoSiHitsCut(void) const{return m_doSiHitsCut;};
   
   void DoPixHitsCut(const bool value){m_doPixHitsCut = value;};
   bool DoPixHitsCut(void) const{return m_doPixHitsCut;};
   
   void DoTrtHitsCut(const bool value){m_doTrtHitsCut = value;};
   bool DoTrtHitsCut(void) const{return m_doTrtHitsCut;};
   
   void DoBlayerHitsCut(const bool value){m_doBlayerHitsCut = value;};
   bool DoBlayerHitsCut(void) const{return m_doBlayerHitsCut;};
   
   // Functions to set/get cuts
   void SetElectronAuthorCut(const unsigned int author){m_author=author;};
   unsigned int GetElectronAuthor(void) const {return m_author;};
   
   void SetEtaAcceptance(const float etaMax){m_etaMax = etaMax;};
   float GetEtaAcceptance(void) const {return m_etaMax;};
   
   void SetCrackExclusionRegion(const float etaMin,const float etaMax)
   {m_crackEtaMin=etaMin;m_crackEtaMax=etaMax;};
   float GetCrackExclusionRegionEtaMax(void) const {return m_crackEtaMax;};
   float GetCrackExclusionRegionEtaMin(void) const {return m_crackEtaMin;};
   
   void SetObjectQualityMask(const unsigned int oqMask){m_oqMask = oqMask;};
   unsigned int GetObjectQualityMask(void) const {return m_oqMask;};
   
   void SetPtCut(const float pTcut){m_pTcut = pTcut;};
   float GetPtCut(void) const {return m_pTcut;};
   
   void SetTrackPtCut(const float pTcut){m_track_pTcut = pTcut;};
   float GetTrackPtCut(void) const {return m_track_pTcut;};
   
   void SetMinSiHitsCut(const int SiHits){m_siHits = SiHits;};
   int GetMinSiHitsCut(void) const {return m_siHits;};
   
   void SetMinPixHitsCut(const int PixHits){m_pixHits = PixHits;};
   int GetMinPixHitsCut(void) const {return m_pixHits;};
   
   void SetMinTrtHitsCut(const int TRTHits){m_trtHits = TRTHits;};
   int GetMinTrtHitsCut(void) const {return m_trtHits;};
   
   void SetMinBlayerHitsCut(const int bLayerHits){m_bLayerHits = bLayerHits;};
   int GetMinBlayerHitsCut(void) const {return m_bLayerHits;};
   
   void RequireTight(const bool requireTight){m_doTight = requireTight;};
   bool IsTightRequired(void) const {return m_doLoose;};
   
   void RequireMedium(const bool requireMedium){m_doMedium = requireMedium;};
   bool IsMediumRequired(void) const {return m_doMedium;};
   
   void RequireLoose(const bool requireLoose){m_doLoose = requireLoose;};
   bool IsLooseRequired(void) const {return m_doTight;};
   
   // Functions to test if electron passes cut
   bool IsElectronAuthor(Analysis::Electron const * const e) const;
   bool IsInEtaAcceptance(Analysis::Electron const * const e) const;
   bool IsNotInCrackRegion(Analysis::Electron const * const e) const;
   bool IsGoodObjectQuality(Analysis::Electron const * const e) const;
   bool PassesPtCut(Analysis::Electron const * const e) const;
   bool PassesTrackPtCut(Analysis::Electron const * const e) const;
   bool PassesMinSiHitsCut(Analysis::Electron const * const e) const;
   bool PassesMinPixHitsCut(Analysis::Electron const * const e) const;
   bool PassesMinTRTHitsCut(Analysis::Electron const * const e) const;
   bool PassesMinBLayerHitsCut(Analysis::Electron const * const e) const;
   bool IsTight(Analysis::Electron const * const e) const;
   bool IsMedium(Analysis::Electron const * const e) const;
   bool IsLoose(Analysis::Electron const * const e) const;
   
   
   
private:
   
   bool m_doAuthorCut;
   unsigned int m_author;
   
   bool m_doEtaCut;
   float m_etaMax;
   bool m_doCrackCut;
   float m_crackEtaMin,m_crackEtaMax;
   
   bool m_doOqCut;
   unsigned int m_oqMask;
   
   bool m_doPtCut;
   float m_pTcut;
   bool m_doTrackPtCut;
   float m_track_pTcut;
   
   bool m_doSiHitsCut;
   int m_siHits;
   bool m_doPixHitsCut;
   int m_pixHits;
   bool m_doTrtHitsCut;
   int m_trtHits;
   bool m_doBlayerHitsCut;
   int m_bLayerHits;
   
   bool m_doLoose;
   bool m_doMedium;
   bool m_doTight;
   
   
   Athena::MsgStreamMember *m_log;
   
};


#endif

