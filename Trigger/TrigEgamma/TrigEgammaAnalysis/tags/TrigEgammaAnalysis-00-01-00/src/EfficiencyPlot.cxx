#include "TrigEgammaAnalysis/EfficiencyPlot.h"

EfficiencyPlot::EfficiencyPlot(const std::string name,const std::string title,const unsigned int nbinsx,const float xlow,const float xup):
   m_s_name(name),
   m_s_title(title)
{
   
   std::string denom_name = m_s_name + "_denom";
   m_denominator = new TH1D(denom_name.c_str(),m_s_title.c_str(),nbinsx,xlow,xup);
   m_denominator->Sumw2();
   
   std::string numer_name = m_s_name + "_numer";
   m_numerator = new TH1D(numer_name.c_str(),m_s_title.c_str(),nbinsx,xlow,xup);
   m_numerator->Sumw2();
   
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"RateHistory");
   
   m_efficiencyPlot = 0;
   
}

EfficiencyPlot::~EfficiencyPlot(void){
   delete m_denominator;
   m_denominator = 0;
   
   delete m_numerator;
   m_numerator = 0;
   
   delete m_log;
   m_log = 0;
   
}

TH1* EfficiencyPlot::GetResult(void){
   
   if(m_efficiencyPlot != 0) return m_efficiencyPlot;
   
   m_efficiencyPlot = m_numerator->DrawCopy();
   
   m_efficiencyPlot->Divide(m_denominator);
   
   return m_efficiencyPlot;
}

StatusCode EfficiencyPlot::Register(ITHistSvc* histSvc,std::string directoryBase){
   StatusCode sc;
   
   std::string regName;
   
   regName = directoryBase + m_denominator->GetName();
   sc = histSvc->regHist(regName,m_denominator);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_denominator->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   regName = directoryBase + m_numerator->GetName();
   sc = histSvc->regHist(regName,m_numerator);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_numerator->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   return StatusCode::SUCCESS;
}
