#ifndef _TRIGGERSELECTORALG_H_
#define _TRIGGERSELECTORALG_H_


#include "AthenaBaseComps/AthAlgorithm.h"
#include <vector>
#include "TrigDecisionTool/TrigDecisionTool.h"

class NtupEvent;

class TriggerSelectorAlg : public AthAlgorithm
{
  public:
    // These are the standard Athena public member functions.
    TriggerSelectorAlg(const std::string& name, ISvcLocator* pSvcLocator);
    virtual ~TriggerSelectorAlg();
	
    virtual StatusCode initialize();
    virtual StatusCode execute();
    virtual StatusCode finalize();



  protected:

	ToolHandle<Trig::TrigDecisionTool>    m_trigger;
	std::vector<std::string> m_triggerStrings;


};

#endif
