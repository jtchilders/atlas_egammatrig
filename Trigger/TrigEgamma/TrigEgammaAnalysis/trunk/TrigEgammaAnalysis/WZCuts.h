#ifndef _WZCUTS_H_
#define _WZCUTS_H_


#include "Particle/TrackParticle.h" //Reco/Particle

#include "egammaEvent/Electron.h"

namespace Athena{
   class MsgStreamMember;
}

class VxContainer;

class WZCuts{
public:
   WZCuts(void);
   ~WZCuts(void);
   
   bool HasMinimumVertex(VxContainer const * vertices,
                         const unsigned short int numPrimaryVertex = 1,
                         const unsigned short int numTrksAtPrimVertex = 3,
                         const unsigned short int vertexPositionCut = 100
                        ) const;
   
   bool IsMinimumEtElectron(Analysis::Electron const * const e,
                            const float cutInGeV = 20.) const;
   
   bool IsElectronAuthor(Analysis::Electron const * const e,
                         const unsigned int allowedAuthor = (egammaParameters::AuthorElectron | egammaParameters::AuthorSofte)) const;
   bool IsInEtaAcceptance(Analysis::Electron const * const e,
                          const float maxAbsEta = 2.47) const;
   bool IsNotInCrackRegion(Analysis::Electron const * const e,
                           const float minAbsEta = 1.37,
                           const float maxAbsEta = 1.52) const;
   bool IsGoodObjectQuality(Analysis::Electron const * const e,
                            const unsigned int minObjectQuality = egammaPID::BADCLUSELECTRON) const;
   bool PassesPtCut(Analysis::Electron const * const e,
                    const float minPt = 20.) const;
   bool PassesTrackPtCut(Analysis::Electron const * const e,
                         const float minTrackPt = 2.) const;
   bool PassesMinSiHitsCut(Analysis::Electron const * const e,
                           const unsigned short int minSiHits = 7) const;
   bool PassesMinPixHitsCut(Analysis::Electron const * const e,
                            const unsigned short int minPixHits = 1) const;
   bool PassesMinTRTHitsCut(Analysis::Electron const * const e,
                            const unsigned short int minTRTHits = 10) const;
   bool PassesMinBLayerHitsCut(Analysis::Electron const * const e,
                               const unsigned short int minBLayerHits = 1) const;
   bool IsTight(Analysis::Electron const * const e) const;
   bool IsMedium(Analysis::Electron const * const e) const;
   bool IsLoose(Analysis::Electron const * const e) const;
   
   bool PassesEtaRangeCut(Analysis::Electron const * const e,
                          const float maxAbsEta = 2.47,
                          const float minAbsEtaCrack = 1.37,
                          const float maxAbsEtaCrack = 1.52) const;
   
private:
   Athena::MsgStreamMember *m_log;
   
};




#endif 