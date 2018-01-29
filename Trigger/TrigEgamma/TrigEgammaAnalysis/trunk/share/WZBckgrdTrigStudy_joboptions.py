### Output file
from GaudiSvc.GaudiSvcConf import THistSvc
ServiceMgr += THistSvc()
ServiceMgr.THistSvc.Output = ["AANT DATAFILE='output.root' OPT='RECREATE'"]

### Input files
DIR = '/dataDisk/Reprocessed/00179939/data11_7TeV.00179939.physics_EnhancedBias.hltmerge.AOD.c707_c708_j7/*'
from glob import glob
filelist = glob(DIR)


### Number of events (-1 = all)
theApp.EvtMax = -1

from TrigEgammaAnalysis.TrigEgammaAnalysisConf import WZBackgroudTriggerStudy
myJob = WZBackgroudTriggerStudy( 'WZBackgroudTriggerStudy' )
myJob.offlineJetsCollection = "AntiKt4TopoEMJets"
myJob.offlineMETCollection  = "MET_RefFinal"
### Level of output spewing into the terminal (DEBUG, INFO, WARNING, ERROR, FATAL)
myJob.OutputLevel = INFO

from AthenaCommon.AlgSequence import AlgSequence, AthSequencer
job = AlgSequence()
job += myJob

import AthenaPoolCnvSvc.ReadAthenaPool
ServiceMgr.EventSelector.InputCollections = filelist

from RecExConfig.RecFlags  import rec
rec.readAOD = True
rec.readRDO = False

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
athenaCommonFlags.FilesInput = filelist

from AthenaCommon.GlobalFlags import globalflags
globalflags.DetGeo = 'atlas'
globalflags.DataSource = 'data'

### Database access
#from IOVDbSvc.CondDB import conddb
#conddb.addFolder('TRIGGER','/TRIGGER/L1Calo/V1/Calibration/Physics/PprChanCalib')
#conddb.addFolder('TRIGGER','/TRIGGER/L1Calo/V1/Calibration/PpmDeadChannels')
#conddb.addFolder('TRIGGER','/TRIGGER/Receivers/Conditions/VgaDac')
#conddb.addFolder('TRIGGER','/TRIGGER/Receivers/Factors/CalibGains')

### Trigger Decision Tool
from TriggerJobOpts.TriggerFlags import TriggerFlags
TriggerFlags.configurationSourceList=['ds']
from TriggerJobOpts.TriggerConfigGetter import TriggerConfigGetter
cfg = TriggerConfigGetter()
