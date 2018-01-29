#ifndef _TRIGELECTRONPLOTS_H_
#define _TRIGELECTRONPLOTS_H_

#include <string>

#include "TrigParticle/TrigElectron.h"
#include "TrigObjectMatching/TrigMatchTool.h"

#include "GaudiKernel/ITHistSvc.h"
#include "GaudiKernel/StatusCode.h"
#include "CLHEP/Units/SystemOfUnits.h"

#include "TH1F.h"
#include "TH2F.h"
#include "Rtypes.h"

namespace Athena{
   class MsgStreamMember;
}
class StatusCode;

class TrigElectronPlots {
public:
   TrigElectronPlots(void);
   ~TrigElectronPlots(void);
   
   void SetColor(Color_t color){m_color = color;};
   
   StatusCode RegisterHistograms(ITHistSvc *histSvc,const std::string dir = "");
   
   void Fill(TrigMatch::TrigElectronL2 const * const electron);
   
private:
   
   Athena::MsgStreamMember *m_log;
   
   TH1F* RegisterTH1F(ITHistSvc *histSvc,std::string dir,
                      std::string name,std::string title,
                      int nbin,float min,float max);
   TH2F* RegisterTH2F(ITHistSvc *histSvc,std::string dir,
                      std::string name,std::string title,
                      int nbinx,float xmin,float xmax,
                      int nbiny,float ymin,float ymax);
   
   Color_t m_color;
   
   // TrigElectron (L2 reco) tracking variables
   std::string m_TrigElectronDir;
   
   std::string m_trackDir;
   
   // General TH1F histograms
   
   TH1F *m_h1f_charge;
   
   
   // TH1F Track histograms
   
   TH1F *m_h1f_track_algoId; // NULL=0,SiTrack=1,IDScan=2,TRTLUT=3,TRTXK=4
   
   TH1F *m_h1f_track_NPixelSpacePoints;
   TH1F *m_h1f_track_NSctSpacePoints;
   TH1F *m_h1f_track_hitPattern;
   
   TH1F *m_h1f_track_nTrtStrawHits;
   TH1F *m_h1f_track_nTrtStraw;
   TH1F *m_h1f_track_nTrtStrawTime;
   TH1F *m_h1f_track_nTrtHighThresholdHits;
   
   TH1F *m_h1f_track_trtHitsRatio;
   
   TH1F *m_h1f_track_chi2;
   
   TH1F *m_h1f_track_a0;
   TH1F *m_h1f_track_ea0;
   TH1F *m_h1f_track_z0;
   TH1F *m_h1f_track_ez0;
   TH1F *m_h1f_track_phi0;
   TH1F *m_h1f_track_ephi0;
   TH1F *m_h1f_track_eta;
   TH1F *m_h1f_track_eeta;
   TH1F *m_h1f_track_pt;
   TH1F *m_h1f_track_ept;
   
   
   // track extrapolated to calorimeter face
   TH1F *m_h1f_trkEtaAtCalo;
   TH1F *m_h1f_trkPhiAtCalo;
   
   TH1F *m_h1f_trkClusDeta;
   TH1F *m_h1f_trkClusDphi;
   TH1F *m_h1f_deltaEta1;
   TH1F *m_h1f_deltaPhi2;
   
   TH1F *m_h1f_etOverPt;
   TH1F *m_h1f_caloEta;
   TH1F *m_h1f_caloPhi;
   
   TH1F *m_h1f_rEta;
   TH1F *m_h1f_eRatio;
   TH1F *m_h1f_etHad1;
   
   
   
};



#endif
