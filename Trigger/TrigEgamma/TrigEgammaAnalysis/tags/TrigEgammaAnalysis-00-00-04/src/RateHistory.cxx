#include "TrigEgammaAnalysis/RateHistory.h"

RateHistory::RateHistory(std::string name, std::string title):
   m_histo(0),
   m_prescaleCorrectedHisto(0),
   m_log(0)
{
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"RateHistory");
   
   // create normal histogram
   m_histo = new TH1F(name.c_str(),title.c_str(),xbins,xmin,xmax);
   //m_histo->Sumw2();
   // create corrected histogram
   std::string prescaleName = name + "_prescaleCorrected";
   std::string prescaleTitle = title + " with Prescale Correction";
   m_prescaleCorrectedHisto = new TH1F(prescaleName.c_str(),prescaleTitle.c_str(),xbins,xmin,xmax);
   //m_prescaleCorrectedHisto->Sumw2();
   
   
}

StatusCode RateHistory::Register(ITHistSvc* histSvc,std::string directoryBase){
   StatusCode sc;
   
   std::string regName;
   
   regName = directoryBase + m_histo->GetName();
   sc = histSvc->regHist(regName,m_histo);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_histo->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   regName = directoryBase + m_prescaleCorrectedHisto->GetName();
   sc = histSvc->regHist(regName,m_prescaleCorrectedHisto);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << " Could not register " << m_prescaleCorrectedHisto->GetName() << " to directory: " << regName << endreq;
      return sc;
   }
   
   return StatusCode::SUCCESS;
}

RateHistory::~RateHistory(void){
   if(m_histo!=0){
      delete m_histo;
      m_histo = 0;
   }
   
   if(m_prescaleCorrectedHisto!=0){
      delete m_prescaleCorrectedHisto;
      m_prescaleCorrectedHisto = 0;
   }
   
   delete m_log;
   m_log = 0;
}

void RateHistory::Fill(const unsigned short int lumiNumber,const float prescale){
   
   m_histo->Fill(lumiNumber);
   m_prescaleCorrectedHisto->Fill(lumiNumber,prescale);
   
   // make sure there is a prescale for every lumiblock
   std::map<unsigned short int,float>::iterator itr = m_map_lbn_prescale.find(lumiNumber);
   
   if(itr == m_map_lbn_prescale.end()){
      m_map_lbn_prescale[lumiNumber] = prescale;
   }
   else{
      itr->second = prescale;
   }
   
}

void RateHistory::BuildHisto(void){
   
   std::map<unsigned short int,float>::iterator itr = m_map_lbn_prescale.end();
   
   itr = m_map_lbn_prescale.begin();
   for(int bin=1;bin<m_histo->GetNbinsX();++bin){
      const float binEntries = m_histo->GetBinContent(bin);
      if(binEntries <= 0) continue;
      
      const unsigned short int lumiNum = bin - 1;
      float rateInHz = binEntries/(float)m_secPerLumiBlock;
      m_histo->SetBinContent(bin,rateInHz);
      
      itr = m_map_lbn_prescale.find(lumiNum);
      float prescale = 1.;
      if(itr == m_map_lbn_prescale.end()) prescale = 0.;
      else prescale = itr->second;
      
      float correctedRateInHz = 0.;
      if(prescale > 0.005) // prescale < 0 means disabled
         correctedRateInHz = rateInHz*prescale;
      m_prescaleCorrectedHisto->SetBinContent(bin,correctedRateInHz);
   }
   
}

