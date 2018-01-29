#ifndef _HISTOGRAMMANAGER_H_
#define _HISTOGRAMMANAGER_H_

#include <string>
#include <map>
#include <exception>

class TH1;
class TH2;
class ITHistSvc;

namespace Athena{
   class MsgStreamMember;
}
class StatusCode;

class HistogramManager {
public:
   HistogramManager(ITHistSvc *histSvc = 0,std::string baseDirectory = "/AANT/");
   ~HistogramManager(void);
   
   
   StatusCode AddTH1F(const std::string dir,
                   const std::string name,const std::string title,
                   const int nbinX,const float xmin,const float xmax);
   
   StatusCode AddTH2F(const std::string dir,
                   const std::string name,const std::string title,
                   const int nbinX,const float xmin,const float xmax,
                   const int nbinY,const float ymin,const float ymax);
   
   StatusCode FillTH1(const std::string name,
                      const float xValue,
                      const float weight = 1) const;
   StatusCode FillTH2(const std::string name,
                      const float xValue,const float yValue,
                      const float weight = 1) const;
   
private:
   HistogramManager();
   HistogramManager(const HistogramManager& hm);
   HistogramManager& operator=(const HistogramManager& hm);
   
   Athena::MsgStreamMember *m_log;
   
   ITHistSvc *m_histSvc;
   std::string m_baseDir;
   
   std::map<std::string,TH1*> m_th1;
   std::map<std::string,TH2*> m_th2;
   
   template <class histType>
   StatusCode Register(const std::string dir,histType* histo);
   
};



#endif
