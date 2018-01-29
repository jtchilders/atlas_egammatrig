#ifndef _WZHistos_H_
#define _WZHistos_H_

#include <string>
#include <vector>

#include "TrigEgammaAnalysis/HistogramManager.h"

namespace Athena{
   class MsgStreamMember;
}
class StatusCode;

// list of names of the histograms so one can use them in the analysis code
// and this class
class WZHistoList {
public:
   
   std::string offElectrons;
   
   std::string offJets;
   
   std::string offJets_jet1;
   std::string offJets_jet2;
   
   std::string transverseMass;
   
   std::string missingEt;
   
   std::vector<std::string> triggers;
   
   std::string failedCuts;
   
   WZHistoList(void){
      
      triggers.push_back("EF_e20_loose_2j10_a4tc_EFFS");
      triggers.push_back("EF_e20_loose_3j10_a4tc_EFFS");
      triggers.push_back("EF_e20_loose_4j10_a4tc_EFFS");
      triggers.push_back("EF_e20_loose");
      triggers.push_back("EF_e20_medium");
      triggers.push_back("EF_e20_medium1");
      triggers.push_back("EF_e20_medium2");
      triggers.push_back("EF_e20_tight");
      triggers.push_back("EF_e22_loose");
      triggers.push_back("EF_e22_medium");
      triggers.push_back("EF_e22_medium1");
      triggers.push_back("EF_e22_medium2");
      triggers.push_back("EF_e22_tight");
      
      
      offElectrons       = "offElectrons";
      
      offJets            = "offJets";
      
      offJets_jet1       = "offJets_jet1";
      offJets_jet2       = "offJets_jet2";
      
      transverseMass     = "M_transverse_noCuts";
      
      missingEt          = "missingEt";
      
      failedCuts         = "failedCuts";
   };
};

class WZHistos: public HistogramManager{
public:
   WZHistos(ITHistSvc *histSvc,std::string baseDirectory = "/AANT/");
   ~WZHistos(void);
   
   enum FAILED_CUTS{
      N_Events = 0,
      Vertex,
      N_Electrons,
      Elec_Pt,
      Elec_Eta,
      Elec_MedNotTight,
      Elec_iso,
      Elec_trigger,
      NumberOfCuts
   };
   
   
   StatusCode FillTH1_EtaPhiET(const std::string name,
                               const float etaValue,
                               const float phiValue,
                               const float etValue) const;
   StatusCode AddTH1F_EtaPhiET(
         const std::string name, const std::string title,const std::string directory,
         const unsigned int etaNbins = 50,const float etaMin = -2.5,const float etaMax = 2.5,
         const unsigned int phiNbins = 64,const float phiMin = -PI,const float phiMax = PI,
         const unsigned int etNbins = 500, const float etMin = 0., const float etMax = 500.
                              );
   
   StatusCode FillTH1_electrons(const std::string trigger,const float eta, const float phi, const float et);
   StatusCode FillTH1_jets(const std::string trigger,const float eta, const float phi, const float et);
   StatusCode FillTH1_missingEt(const std::string trigger,const float missingEt);
   
   StatusCode FillTH1_failedCuts(const FAILED_CUTS cut);
   
private:
   WZHistos();
   WZHistos(const WZHistos& hm);
   WZHistos& operator=(const WZHistos& hm);
   
   void CreateHistos(void);
   void InitializeHistoNames(void);
   
   static const float PI;
   
   WZHistoList* m_histoList;
   
   Athena::MsgStreamMember* m_log;
   
   void AddTH1F_missingEt(const std::string trigger = "");
   void AddTH1F_jets(const std::string trigger = "");
   void AddTH1F_electrons(const std::string trigger = "");
   
   void AddTH1F_failedCuts(void);
};

#endif
