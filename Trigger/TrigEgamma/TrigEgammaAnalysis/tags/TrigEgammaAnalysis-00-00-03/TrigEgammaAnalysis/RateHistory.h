/// /////////////////////////////////////////////////
/// Plots the number rate as a function of
/// Lumi-block.
/// Author: Taylor Childers
/// /////////////////////////////////////////////////
#ifndef RATEHISTORY_H
#define RATEHISTORY_H

#include <map>
#include <string>

#include "TH1F.h"

#include "GaudiKernel/ITHistSvc.h"
#include "AthenaKernel/MsgStreamMember.h"

class RateHistory{
public:
   RateHistory(std::string name, std::string title);
   ~RateHistory(void);
   
   TH1F* GetHisto(void) const {return m_histo;};
   TH1F* GetPrescaleCorrectedHisto(void) const {return m_prescaleCorrectedHisto;};
   
   std::string GetName(void) const {return (std::string)m_histo->GetName();};
   std::string GetTitle(void) const {return (std::string)m_histo->GetTitle();};
   
   StatusCode Register(ITHistSvc* histSvc,std::string directoryBase);
   
   void Fill(const unsigned short int lumiNumber,const float prescale = 1);
   
   void BuildHisto(void);
   
   void SetLineColor(int color){if(m_histo!=0)m_histo->SetLineColor(color);
      if(m_prescaleCorrectedHisto!=0)m_prescaleCorrectedHisto->SetLineColor(color);};
   
private:
   TH1F *m_histo;
   TH1F *m_prescaleCorrectedHisto;
   
   std::map<unsigned short int,float> m_map_lbn_prescale;
   
   // default for most physics runs as of Aug 3 2010.
   static const unsigned int m_secPerLumiBlock = 120;
   
   static const unsigned int xbins = 1000;
   static const unsigned int xmax  = 1000;
   static const unsigned int xmin  =    0;
   
   Athena::MsgStreamMember *m_log;
};




#endif
