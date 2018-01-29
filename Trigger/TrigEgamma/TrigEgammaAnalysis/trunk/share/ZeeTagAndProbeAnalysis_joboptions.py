### Output file
from GaudiSvc.GaudiSvcConf import THistSvc
ServiceMgr += THistSvc()
ServiceMgr.THistSvc.Output = ["AANT DATAFILE='output.root' OPT='RECREATE'"]

### Input files
DIR = '/dataDisk/Collisions/Zee/periodI_Zee/*/*'
from glob import glob
filelist = glob(DIR)

### Number of events (-1 = all)
nEvents = -1

from TrigEgammaAnalysis.TrigEgammaAnalysisConf import TrigEgammaZeeTagAndProbeAnalysis
L1eg = TrigEgammaZeeTagAndProbeAnalysis( 'TrigEgammaZeeTagAndProbeAnalysis' )


### Level of output spewing into the terminal (DEBUG, INFO, WARNING, ERROR, FATAL)
L1eg.OutputLevel = INFO


from RecExConfig.RecFlags  import rec
rec.readAOD.set_Value_and_Lock(True)
rec.doTile.set_Value_and_Lock(False)
rec.doLArg.set_Value_and_Lock(False)

disableRecJobOpts = ('doAlfa','doApplyAODFix','doTrigger','doTruth','doAOD',
   'doAODCaloCells','doAODall','doCheckDictionary','doCheckJOT','doDetStatus',
   'doCBNT','readESD','CBNTAthenaAware','doPerfMon','oldFlagTopSteering',
   'doHist','doDetailedPerfMon','doWriteAOD','doWriteTAG','doDetailedAuditor',
   'doJetMissingETTag','doEgamma','readRDO','doMuonCombined','doDumpMC',
   'doTau','doMonitoring','doWriteESD','doDumpPoolInputContent',
   'doDPD','doLucid','doForwardDet','doInDet','doDumpProperties','doDumpTDS','doEdmMonitor',
   'doFileMetaData','doFloatingPointException','doHeavyIon','doJetMissingETTag',
   'doJiveXML','doLowPt','doMinimalRec','doMuon','doNameAuditor','doPersint','doPyDump',
   'doRestrictedESD','doSGAuditor','doShowSizeStatistics','doTagRawSummary','doTimeLimit',
   'doVP1','doWriteBS','doWriteRDO','doWriteTAGCOM','doZdc','readAOD','readTAG'
      )
for p in disableRecJobOpts:
   getattr(rec, p).set_Value_and_Lock(False)

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
athenaCommonFlags.PoolAODInput.set_Value_and_Lock(filelist)
athenaCommonFlags.EvtMax.set_Value_and_Lock(nEvents)

from AthenaCommon.GlobalFlags import GlobalFlags,globalflags
GlobalFlags.DataSource.set_data()
#globalflags.ConditionsTag.set_Value_and_Lock('COMCOND-BLKPST-004-00')
#globalflags.DetDescrVersion.set_Value_and_Lock('ATLAS-GEO-10-00-01')

rec.AutoConfiguration=['everything']

from AthenaCommon.AlgSequence import AlgSequence, AthSequencer
job = AlgSequence()


# add LumiBlockMetaDataTool to ToolSvc and configure
#from LumiBlockComps.LumiBlockCompsConf import LumiBlockMetaDataTool
#ToolSvc += LumiBlockMetaDataTool( "LumiBlockMetaDataTool" )
#LumiBlockMetaDataTool.calcLumi = False # False by default
#LumiBlockMetaDataTool.storeXMLFiles = False
#LumiBlockMetaDataTool.applyDQCuts = False
#LumiBlockMetaDataTool.OutputLevel = DEBUG

#add ToolSvc.LumiBlockMetaDataTool to MetaDataSvc
#from EventSelectorAthenaPool.EventSelectorAthenaPoolConf import MetaDataSvc
#svcMgr += MetaDataSvc( "MetaDataSvc" )
#svcMgr.MetaDataSvc.MetaDataTools += [ ToolSvc.LumiBlockMetaDataTool ]

# Configure the goodrunslist selector tool
from GoodRunsLists.GoodRunsListsConf import *
from GoodRunsListsUser.GoodRunsListsUserConf import *
ToolSvc += GoodRunsListSelectorTool() 
GoodRunsListSelectorTool.OutputLevel = DEBUG
GoodRunsListSelectorTool.GoodRunsListVec = [ 'data10_7TeV.periodI.167575-167844_LBSUMM_DetStatus-v03-pass1-analysis-2010I_eg_standard_7TeV.xml' ]
# 'data10_7TeV.periodH.166466-166964_LBSUMM_DetStatus-v03-pass1-analysis-2010H_data_eg_standard_7TeV.xml' ]
GoodRunsListSelectorTool.PassThrough = False
seq = AthSequencer("AthFilterSeq")
seq += GRLTriggerSelectorAlg('MyLBCollection')

# add LumiCalcSvc to ServiceMgr and configure
#from LumiBlockComps.LumiBlockCompsConf import LumiCalcSvc
#LumiCalcSvc = LumiCalcSvc()
#LumiCalcSvc.Triggers = ["L1_EM2"]
#LumiCalcSvc.UseMC = False
#LumiCalcSvc.LBCollNames = ["LumiBlocks", "IncompleteLumiBlocks"]
#LumiCalcSvc.Verbose = False
#svcMgr += LumiCalcSvc


#include('TileRecAlgs/TileCellToTTL1_jobOptions.py')
include('RecExCommon/RecExCommon_topOptions.py')
job += L1eg

### Database access
from IOVDbSvc.CondDB import conddb
conddb.addFolder('TRIGGER','/TRIGGER/L1Calo/V1/Calibration/Physics/PprChanCalib')
conddb.addFolder('TRIGGER','/TRIGGER/L1Calo/V1/Calibration/PpmDeadChannels')
conddb.addFolder('TRIGGER','/TRIGGER/Receivers/Conditions/VgaDac')
conddb.addFolder('TRIGGER','/TRIGGER/Receivers/Factors/CalibGains')

### Trigger Decision Tool
from TrigDecisionTool.TrigDecisionToolConf import Trig__TrigDecisionTool
tdt = Trig__TrigDecisionTool('TrigDecisionTool')
ToolSvc += tdt
tdt.OutputLevel=WARNING
ToolSvc.TrigDecisionTool.Navigation.OutputLevel = WARNING
from TriggerJobOpts.TriggerFlags import TriggerFlags
TriggerFlags.configurationSourceList=['ds']
from TriggerJobOpts.TriggerConfigGetter import TriggerConfigGetter
cfg = TriggerConfigGetter()
