#ifndef _L2VSOFFLINEELECTRONPLOTS_H_
#define _L2VSOFFLINEELECTRONPLOTS_H_

#include <string>

#include "TrigParticle/TrigElectron.h"
#include "TrigObjectMatching/TrigMatchTool.h"

#include "egammaEvent/Electron.h"

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

class L2vsOfflineElectronPlots {
public:
   L2vsOfflineElectronPlots(void);
   ~L2vsOfflineElectronPlots(void);
   
   void SetColor(Color_t color){m_color = color;};
   
   StatusCode RegisterHistograms(ITHistSvc *histSvc,const std::string dir = "");
   
   void Fill(TrigMatch::TrigElectronL2 const * const l2Electron,Analysis::Electron const * const offElectron);
   
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
   
   
   
   
   // TH1F Track histograms
   
   TH1F *m_h1f_diff_nSctHits;
   TH1F *m_h1f_diff_nPixHits;
   TH1F *m_h1f_diff_nTrtHits;
   TH1F *m_h1f_diff_nTrtHiHits;
   
   TH1F *m_h1f_diff_nSctHitsOutlier;
   TH1F *m_h1f_diff_nPixHitsOutlier;
   TH1F *m_h1f_diff_nTrtHitsOutlier;
   TH1F *m_h1f_diff_nTrtHiHitsOutlier;
   
   TH1F *m_h1f_diff_eta;
   TH1F *m_h1f_diff_phi;
   
   TH1F *m_h1f_diff_pt;
   TH1F *m_h1f_diff_et;
   
   TH1F *m_h1f_diff_track_pt;
   
   TH1F *m_h1f_diff_z0;
   TH1F *m_h1f_diff_a0;
   TH1F *m_h1f_diff_phi0;
   
   static const float PI;
   
};



#endif
