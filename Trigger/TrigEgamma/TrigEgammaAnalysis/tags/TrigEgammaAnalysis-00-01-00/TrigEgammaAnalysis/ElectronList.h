#ifndef _ELECTRONLIST_H_
#define _ELECTRONLIST_H_

#include <vector>

#include "AthenaKernel/MsgStreamMember.h"
#include "egammaEvent/Electron.h"
#include "egammaEvent/ElectronContainer.h"

#include "TrigDecisionTool/TrigDecisionTool.h"
#include "TrigDecisionTool/ChainGroup.h"
#include "TrigObjectMatching/TrigMatchTool.h"

#include "TrigEgammaAnalysis/ElectronCuts.h"

class ElectronList{
public:
   ElectronList(ElectronCuts const * const cuts);
   ~ElectronList(void);
   
   bool FillList(const ElectronContainer* electrons,ToolHandle<TrigMatchTool>& trigMatch,std::string passingChain);
   
   std::vector<Analysis::Electron*>* GetList(void){return m_elist;};
   
   typedef std::vector<Analysis::Electron*>::iterator list_iterator;
   list_iterator begin(void){return m_elist->begin();};
   list_iterator end(void){return m_elist->end();};
   
   Analysis::Electron* at(unsigned int index){if(m_elist->size() > 0) return m_elist->at(index); return (Analysis::Electron*)0;};
   
   void clear(void){m_elist->clear();};
   
   unsigned int size(void){return m_elist->size();};
   
   bool IsEmpty(void){if(m_elist->size() > 0) return false; return true;};
   
private:
   std::vector<Analysis::Electron*> *m_elist;
   
   ElectronCuts const * m_cuts;
   
   Athena::MsgStreamMember *m_log;
   
};


#endif

