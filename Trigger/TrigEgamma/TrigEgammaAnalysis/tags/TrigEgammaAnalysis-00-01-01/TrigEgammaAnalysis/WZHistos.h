#ifndef _WZHistos_H_
#define _WZHistos_H_

#include <string>

#include "TrigEgammaAnalysis/HistogramManager.h"

namespace Athena{
   class MsgStreamMember;
}
class StatusCode;

// list of names of the histograms so one can use them in the analysis code
// and this class
class WZHistoList {
public:
   
   std::string offElectrons_noCuts;
   std::string offElectrons_e20_loose_2j10_a4tc_EFFS;
   std::string offElectrons_e20_loose_3j10_a4tc_EFFS;
   std::string offElectrons_e20_loose_4j10_a4tc_EFFS;
   
   std::string offJets_noCuts;
   std::string offJets_e20_loose_2j10_a4tc_EFFS;
   std::string offJets_e20_loose_3j10_a4tc_EFFS;
   std::string offJets_e20_loose_4j10_a4tc_EFFS;
   
   std::string offJets_jet1;
   std::string offJets_jet2;
   
   std::string transverseMass;
   
   std::string missingEt;
   std::string missingEt_e20_loose_2j10_a4tc_EFFS;
   std::string missingEt_e20_loose_3j10_a4tc_EFFS;
   std::string missingEt_e20_loose_4j10_a4tc_EFFS;
   
   
   WZHistoList(void){
      
      offElectrons_noCuts                   = "offElectrons_noCuts";
      offElectrons_e20_loose_2j10_a4tc_EFFS = "offEl_passing_e20l_2j10";
      offElectrons_e20_loose_3j10_a4tc_EFFS = "offEl_passing_e20l_3j10";
      offElectrons_e20_loose_4j10_a4tc_EFFS = "offEl_passing_e20l_4j10";
      
      offJets_noCuts                        = "offJets_noCuts";
      offElectrons_e20_loose_2j10_a4tc_EFFS = "offJets_passing_e20l_2j10";
      offElectrons_e20_loose_3j10_a4tc_EFFS = "offJets_passing_e20l_3j10";
      offElectrons_e20_loose_4j10_a4tc_EFFS = "offJets_passing_e20l_4j10";
      
      offJets_jet1 = "offJets_jet1";
      offJets_jet2 = "offJets_jet2";
      
      transverseMass      = "M_transverse_noCuts";
      
      missingEt                          = "missingEt_noCuts";
      missingEt_e20_loose_2j10_a4tc_EFFS = "misEt_passing_e20l_2j10";
      missingEt_e20_loose_3j10_a4tc_EFFS = "misEt_passing_e20l_3j10";
      missingEt_e20_loose_4j10_a4tc_EFFS = "misEt_passing_e20l_4j10";
   };
};

class WZHistos: public HistogramManager{
public:
   WZHistos(ITHistSvc *histSvc,std::string baseDirectory = "/AANT/");
   ~WZHistos(void);
   
   
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
   
private:
   WZHistos();
   WZHistos(const WZHistos& hm);
   WZHistos& operator=(const WZHistos& hm);
   
   void CreateHistos(void);
   void InitializeHistoNames(void);
   
   static const float PI;
   
   WZHistoList* histoList;
   
   Athena::MsgStreamMember* m_log;
   
   
};

#endif