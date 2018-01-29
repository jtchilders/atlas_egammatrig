#include "TrigEgammaAnalysis/HistogramManager.h"

#include "AthenaKernel/MsgStreamMember.h"
#include "GaudiKernel/StatusCode.h"
#include "GaudiKernel/ITHistSvc.h"

#include "TH1C.h"
#include "TH1I.h"
#include "TH1S.h"
#include "TH1F.h"
#include "TH1D.h"

#include "TH2C.h"
#include "TH2I.h"
#include "TH2S.h"
#include "TH2F.h"
#include "TH2D.h"

#include "TProfile.h"
#include "TProfile2D.h"


HistogramManager::HistogramManager(ITHistSvc *histSvc,std::string baseDirectory):
   m_histSvc(histSvc),
   m_baseDir(baseDirectory)
{
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"HistogramManager");
   
   
}

HistogramManager::~HistogramManager(void)
{
   delete m_log;
   m_log = 0;
}


StatusCode HistogramManager::AddTH1F(const std::string dir,
                                  const std::string name,const std::string title,
                                  const int nbinX,const float xmin,const float xmax)
{
   // create histogram
   TH1F* histo = new TH1F(name.c_str(),title.c_str(),nbinX,xmin,xmax);
   
   // add histogram to map using name as key
   try{
      m_th1[name] = dynamic_cast<TH1*>(histo);
   }catch(std::exception& e){
      *m_log << MSG::ERROR << "[TH1F] Map Exception Caught: " << e.what() << endreq;
      return StatusCode::FAILURE;
   }
   
   // register histogram
   StatusCode sc = Register<TH1F>(dir,histo);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[TH1F] Failed to register histogram named: " << name << endreq;
      return sc;
   }
   
   return StatusCode::SUCCESS;
}

StatusCode HistogramManager::FillTH1(const std::string name,
                                     const float xValue,
                                     const float weight) const
{
   // retrieve histogram from map by name
   TH1* hist = GetTH1(name);
   if(hist == 0){
      *m_log << MSG::ERROR << "[FillTH1] Failed to find histogram named: " << name << endreq;
      return StatusCode::FAILURE;
   }
   
   // Fill histogram
   hist->Fill(xValue,weight);
   
   return StatusCode::SUCCESS;
}

TH1* HistogramManager::GetTH1(const std::string name) const{
   // retrieve histogram from map by name
   std::map<std::string,TH1*>::const_iterator hist = m_th1.find(name);
   if(hist == m_th1.end()){
      *m_log << MSG::ERROR << "[GetTH1] Failed to find histogram named: " << name << endreq;
      return (TH1*)0;
   }
   
   return hist->second;
}


StatusCode HistogramManager::AddTH2F(const std::string dir,
                                  const std::string name,const std::string title,
                                  const int nbinX,const float xmin,const float xmax,
                                  const int nbinY,const float ymin,const float ymax)
{
   // create histogram
   TH2F *histo = new TH2F(name.c_str(),title.c_str(),nbinX,xmin,xmax,nbinY,ymin,ymax);
   
   // add histogram to map using name as key
   try{
      m_th2[name] = dynamic_cast<TH2*>(histo);
   }catch(std::exception& e){
      *m_log << MSG::ERROR << "[TH2F] Map Exception Caught: " << e.what() << endreq;
      return StatusCode::FAILURE;
   }
   
   // register histogram
   StatusCode sc = Register<TH2F>(dir,histo);
   if(sc.isFailure()){
      *m_log << MSG::ERROR << "[TH2F] Failed to register histogram named: " << name << endreq;
      return sc;
   }
   
   return StatusCode::SUCCESS;
}



StatusCode HistogramManager::FillTH2(const std::string name,
                                     const float xValue,const float yValue,
                                     const float weight) const
{
   // retrieve histogram from map by name
   TH2* hist = GetTH2(name);
   if(hist == 0){
      *m_log << MSG::ERROR << "[FillTH2] Failed to find histogram named: " << name << endreq;
      return StatusCode::FAILURE;
   }
   
   // Fill histogram
   
   hist->Fill(xValue,yValue,weight);
   
   return StatusCode::SUCCESS;
}

TH2* HistogramManager::GetTH2(const std::string name) const{
   // retrieve histogram from map by name
   std::map<std::string,TH2*>::const_iterator hist = m_th2.find(name);
   if(hist == m_th2.end()){
      *m_log << MSG::ERROR << "[GetTH2] Failed to find histogram named: " << name << endreq;
      return (TH2*)0;
   }
   
   return hist->second;
}


template <class histType>
StatusCode HistogramManager::Register(const std::string dir,histType* histo)
{
   // check that histo service was provided
   if(m_histSvc != 0){
      std::string directory = m_baseDir;
      if(dir.size() > 0){
         directory += dir;
         // make sure directory already ends with forward slash
         if(dir[dir.size()-1] != '/') directory += "/";
      }
      
      directory += histo->GetName();
      
      StatusCode sc = m_histSvc->regHist(directory,histo);
      if(sc.isFailure()){
         *m_log << MSG::ERROR << "[Register] Failed to register histogram to directory: " << directory << endreq;
         return sc;
      }
   }
   
   return StatusCode::SUCCESS;
}
