#include "DataSelectorAlgs/TriggerSelectorAlg.h"

TriggerSelectorAlg::TriggerSelectorAlg(const std::string& name, ISvcLocator* pSvcLocator) : AthAlgorithm(name, pSvcLocator),
m_trigger("Trig::TrigDecisionTool/TrigDecisionTool")
{
	
	declareProperty("TriggerStrings",m_triggerStrings);

}

TriggerSelectorAlg::~TriggerSelectorAlg(){}


StatusCode TriggerSelectorAlg::initialize() {
	msg(MSG::INFO) << "TriggerSelectorAlg init" << endreq;

	StatusCode sc;
	 //if doing trigger checking, load trigger tool 
		if(m_triggerStrings.size()>0) {
			sc = m_trigger.retrieve();
			if(sc.isFailure()) { msg(MSG::ERROR) << "Need TrigDecisionTool for Trigger checking" << endreq; }
		} else {
			sc = StatusCode::SUCCESS;
		}

	return sc;
}

StatusCode TriggerSelectorAlg::execute() {
	//test the trigger decision if required 
	bool useEvent=false;
		if(m_triggerStrings.size()>0) {
			typedef std::vector<std::string>::iterator Itr_s;
			
			for(Itr_s i=m_triggerStrings.begin();i!=m_triggerStrings.end();++i){
				//want to look for trigger passing after prescale
				if(m_trigger->isPassed(*i) == true){
					useEvent = true; break;
				}
			}
		} else {
			useEvent = true;
		}

	this->setFilterPassed(useEvent);

	return StatusCode::SUCCESS;
}

StatusCode TriggerSelectorAlg::finalize() {
	return StatusCode::SUCCESS;
}

