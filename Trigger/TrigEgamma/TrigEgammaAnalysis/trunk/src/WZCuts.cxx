#include "TrigEgammaAnalysis/WZCuts.h"


#include "AthenaKernel/MsgStreamMember.h"

// for HasMinimumVertex cut
#include "TrkEventPrimitives/VertexType.h"
#include "VxVertex/VxContainer.h"

#include "TrkTrackSummary/TrackSummary.h"

WZCuts::WZCuts(void){
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"WZCuts");
}

WZCuts::~WZCuts(void){
   delete m_log;
   m_log = 0;
}

bool WZCuts::HasMinimumVertex(VxContainer const * vertices,
                              const unsigned short int numPrimaryVertex,
                              const unsigned short int numTrksAtPrimVertex,
                              const unsigned short int vertexPositionCut
                             ) const
{
   VxContainer::const_iterator itr = vertices->begin();
   
   unsigned int numVertices = 0;
   
   // loop over the vertices
   for(;itr != vertices->end();++itr){
      // get pointer to vertex object
      Trk::VxCandidate *vertex = *itr;
      // test for a primary vertex primary vertex
      if(vertex->vertexType() == Trk::PriVtx){
         // test for minimum number of tracks associated with this vertex
         if(vertex->vxTrackAtVertex()->size() >= numTrksAtPrimVertex){
            // test that track vertex is within the vertex position cut
            if(fabs(vertex->recVertex().position().z()) < vertexPositionCut){
               // count vertex if it passes all these conditions
               numVertices++;
               
               // if the number of vertices requirement has been satisfied
               // there is no need to continue counting
               if(numVertices >= numPrimaryVertex)
                  return true;
            
            }// if(within vertex position cut)
         }// if(number of tracks at vertex)
      }// if(primary vertex)
   }// end for(vertices)
   
   return false;
}

bool WZCuts::IsMinimumEtElectron(Analysis::Electron const * const e,const float cutInGeV) const
{
   if( (e->et()/1000.) < cutInGeV) return false;
   return true;
}


bool WZCuts::IsInEtaAcceptance(Analysis::Electron const * const e,
                               const float maxAbsEta) const 
{
   if(fabs(e->eta()) < maxAbsEta)
      return true;
   
   *m_log << MSG::DEBUG << "Failed IsInEtaAcceptance." << endreq;
   return false;
}

bool WZCuts::IsNotInCrackRegion(Analysis::Electron const * const e,
                                const float minAbsEta,
                                const float maxAbsEta) const 
{
   const float feta = fabs(e->eta());
   if(!(minAbsEta < feta && feta < maxAbsEta))
      return true;
   
   *m_log << MSG::DEBUG << "Failed IsNotInCrackRegion." << endreq;
   return false;
}

bool WZCuts::PassesEtaRangeCut(Analysis::Electron const * const e,
                               const float maxAbsEta,
                               const float minAbsEtaCrack,
                               const float maxAbsEtaCrack) const
{
   if(IsInEtaAcceptance(e,maxAbsEta) && IsNotInCrackRegion(e,minAbsEtaCrack,maxAbsEtaCrack))
      return true;
   
   *m_log << MSG::DEBUG << "Failed PassesEtaRangeCut." << endreq;
   return false;
}

bool WZCuts::IsElectronAuthor(Analysis::Electron const * const e,
                              const unsigned int allowedAuthor) const 
{
   if(allowedAuthor & e->author())
      return true;
   
   *m_log << MSG::DEBUG << "Failed IsElectronAuthor." << endreq;
   return false;
}


bool WZCuts::IsGoodObjectQuality(Analysis::Electron const * const e,
                                 const unsigned int minObjectQuality) const
{
   if(!e->isgoodoq(minObjectQuality))
      return true;
   
   *m_log << MSG::DEBUG << "Failed IsGoodObjectQuality." << endreq;
   return false;
}


bool WZCuts::PassesPtCut(Analysis::Electron const * const e,
                         const float minPt) const
{
   float electronPtGeV = e->pt()/GeV;
   if(electronPtGeV > minPt)
      return true;
   
   *m_log << MSG::DEBUG << "Failed PtCut." << endreq;
   return false;
}

bool WZCuts::PassesTrackPtCut(Analysis::Electron const * const e,
                              const float minTrackPt) const
{
   float electronPtGeV = e->trackParticle()->pt()/GeV;
   if(electronPtGeV > minTrackPt)
      return true;
   
   *m_log << MSG::DEBUG << "Failed TrackPtCut." << endreq;
   return false;
}

bool WZCuts::PassesMinSiHitsCut(Analysis::Electron const * const e,
                                const unsigned short int minSiHits) const
{
   const Trk::TrackSummary *sum = e->trackParticle()->trackSummary();
   
   if(sum->get(Trk::numberOfSCTHits) >= minSiHits)
      return true;
   
   *m_log << MSG::DEBUG << "Failed SiHits." << endreq;
   return false;
}

bool WZCuts::PassesMinPixHitsCut(Analysis::Electron const * const e,
                                 const unsigned short int minPixHits) const
{
   const Trk::TrackSummary *sum = e->trackParticle()->trackSummary();
   
   if(sum->get(Trk::numberOfPixelHits) >= minPixHits)
      return true;
   
   *m_log << MSG::DEBUG << "Failed PixHits." << endreq;
   return false;
}

bool WZCuts::PassesMinTRTHitsCut(Analysis::Electron const * const e,
                                 const unsigned short int minTRTHits) const
{
   const Trk::TrackSummary *sum = e->trackParticle()->trackSummary();
   
   if((sum->get(Trk::numberOfTRTHits)+sum->get(Trk::numberOfTRTOutliers)) >= minTRTHits)
      return true;
   
   *m_log << MSG::DEBUG << "Failed TRTHits." << endreq;
   return false;
}

bool WZCuts::PassesMinBLayerHitsCut(Analysis::Electron const * const e,
                                    const unsigned short int minBLayerHits) const
{
   const Trk::TrackSummary *sum = e->trackParticle()->trackSummary();
   
   if(sum->get(Trk::expectBLayerHit) && sum->get(Trk::numberOfBLayerHits) >= minBLayerHits)
      return true;
   
   *m_log << MSG::DEBUG << "Failed bLayerHits." << endreq;
   return false;
}

bool WZCuts::IsTight(Analysis::Electron const * const e) const
{
   // release 16 return e->isElectron(egammaPID::ElectronTight);
   return e->passID(egammaPID::ElectronIDTight);
}

bool WZCuts::IsMedium(Analysis::Electron const * const e) const
{
   // release 16 return e->isElectron(egammaPID::ElectronMedium);
   return e->passID(egammaPID::ElectronIDMedium);
}

bool WZCuts::IsLoose(Analysis::Electron const * const e) const
{
   // release 16 return e->isElectron(egammaPID::ElectronLoose);
   return e->passID(egammaPID::ElectronIDLoose);
}


