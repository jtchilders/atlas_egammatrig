
#include "TrigEgammaAnalysis/ElectronList.h"

ElectronList::ElectronList(ElectronCuts const * const cuts){
   
   m_elist = new std::vector<Analysis::Electron*>;
   m_cuts = cuts;
   
   m_log = new Athena::MsgStreamMember(Athena::Options::Eager,"ElectronList");
}

ElectronList::~ElectronList(void){
   
   delete m_elist;
   m_elist = 0;
   
   delete m_log;
   m_log = 0;
}

bool ElectronList::FillList(const ElectronContainer* electrons,ToolHandle<TrigMatchTool>& trigMatch,std::string passingChain){
   
   m_elist->clear();
   
   ElectronContainer::const_iterator itr = electrons->begin();
   
   // loop over the electrons
   for(;itr!=electrons->end();++itr){
      Analysis::Electron* e = (*itr);
      if(m_cuts->IsGoodElectron(e)){
         
         // check if electron is matching the trigger chain passed
         if(!passingChain.empty())
            if(!trigMatch->chainPassedByObject<TrigMatch::TrigElectronEF>(e,passingChain,0.15))
               break;
         
         m_elist->push_back(e);
         
      }// end if(goodElectron)
   }// end for(electron)
   
   if(IsEmpty())
      return false;
   
   return true;
   
}

