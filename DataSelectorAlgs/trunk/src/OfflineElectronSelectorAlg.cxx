#include "DataSelectorAlgs/OfflineElectronSelectorAlg.h"

#include "GaudiKernel/MsgStream.h"

OfflineElectronSelectorAlg::OfflineElectronSelectorAlg(const std::string& name, ISvcLocator* pSvcLocator) : AthAlgorithm(name, pSvcLocator),m_storeGate("StoreGateSvc", name)
{
   
   declareProperty("ElectronContainerName",m_offlineElectronsName = "ElectronAODCollection");
   declareProperty("ElectronEtCut",m_electronEtCut = 0.);
   declareProperty("ElectronEtaCut",m_electronEtaCut = 999.);
   
   m_offlineElectrons = 0;
   
   m_n_events = 0;
   
}

OfflineElectronSelectorAlg::~OfflineElectronSelectorAlg(){}


StatusCode OfflineElectronSelectorAlg::initialize() {
   msg(MSG::INFO) << "TriggerSelectorAlg init" << endreq;
   
   StatusCode sc;
   
   msg(MSG::INFO) << "Electron ET Cut Set to: " << m_electronEtCut << " Electron ETA Cut Set to: " << m_electronEtaCut << endreq;
   
   m_useEtCut = true;
   if(fabs(m_electronEtCut) < 0.005) m_useEtCut = false;
   
   m_useEtaCut = true;
   if(fabs(m_electronEtaCut - 999.) < 0.005) m_useEtaCut = false;
   
   return sc;
}

StatusCode OfflineElectronSelectorAlg::execute() {
   //test the trigger decision if required 
   bool useEvent=false;
   
   // Load offline electrons
   StatusCode sc = m_storeGate->retrieve(m_offlineElectrons,m_offlineElectronsName);
   if(sc.isFailure()){
      msg(MSG::INFO) << "Failed to load" << m_offlineElectronsName << endreq;
      return sc;
   }
   
   for(unsigned int i = 0;i < m_offlineElectrons->size();++i){
      
      Analysis::Electron const * const e = m_offlineElectrons->at(i);
      
      msg(MSG::DEBUG) << "Electron[" << i << "] ET = " << (e->et()/1000.) << " cut[" << m_useEtCut << "]: " << m_electronEtCut << " eta = " << e->eta() << " cut[" << m_useEtaCut << "]: " << m_electronEtaCut << 
      endreq;
      
      if( m_useEtCut && m_useEtaCut){
         if( (e->et()/1000.) > m_electronEtCut &&
              fabs(e->eta()) < m_electronEtaCut){
            useEvent = true;
            msg(MSG::DEBUG) << "Passed both cuts." << endreq;
            break;
         }
      }
      else if(m_useEtCut){
         if( (e->et()/1000.) > m_electronEtCut){
            useEvent = true;
            msg(MSG::DEBUG) << "Passed ET cut." << endreq;
            break;
         }
      }
      else if(m_useEtaCut){
         if( fabs(e->eta()) < m_electronEtaCut){
            useEvent = true;
            msg(MSG::DEBUG) << "Passed  eta cuts." << endreq;
            break;
         }
      }
      
   }// end for(electrons)
   
   if(useEvent){
      m_n_events++;
      msg(MSG::DEBUG) << "Event Passed." << endreq;
   }
   else
      msg(MSG::DEBUG) << "Event Failed." << endreq;
      
   
   this->setFilterPassed(useEvent);
   
   return sc;
}

StatusCode OfflineElectronSelectorAlg::finalize() {
   msg(MSG::INFO) << "Events passed: " << m_n_events << endreq;
   return StatusCode::SUCCESS;
}

