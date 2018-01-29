#ifndef EFFICIENCYPLOT_H
#define EFFICIENCYPLOT_H

#include <string>

#include "TH1D.h"

#include "GaudiKernel/ITHistSvc.h"
#include "AthenaKernel/MsgStreamMember.h"

class EfficiencyPlot{
public:
   EfficiencyPlot(const std::string name,const std::string title,const unsigned int nbinsx,const float xlow,const float xup);
   ~EfficiencyPlot(void);
   
   StatusCode Register(ITHistSvc* histSvc,std::string directoryBase);
   
   void FillDenominator(double x){m_denominator->Fill(x);};
   void FillNumerator(double x){m_numerator->Fill(x);};
   
   std::string GetName(void){return m_s_name;};
   std::string GetTitle(void){return m_s_title;};
   
   TH1D* GetDenominator(void){return m_denominator;};
   TH1D* GetNumerator(void){return m_numerator;};
   
   TH1* GetResult(void);
   
private:
   // make default copy constructor private
   EfficiencyPlot(const EfficiencyPlot&){};
   
   std::string m_s_name;
   std::string m_s_title;
   
   TH1D *m_denominator;
   TH1D *m_numerator;
   
   TH1 *m_efficiencyPlot;
   
   Athena::MsgStreamMember *m_log;
};



#endif

