### Output file
#from GaudiSvc.GaudiSvcConf import THistSvc
#ServiceMgr += THistSvc()
#ServiceMgr.THistSvc.Output = ["AANT DATAFILE='output.root' OPT='RECREATE'"]

### Input files
DIR = '/dataDisk/Reprocessed/00179939/data11_7TeV.00179939.physics_EnhancedBias.hltmerge.AOD.c707_c708_j7/*'
from glob import glob
filelist = glob(DIR)

theApp.EvtMax = -1

MessageSvc.useColors = True
MessageSvc.debugLimit = 500000

from AthenaCommon.AlgSequence import AthSequencer
seq = AthSequencer("AthFilterSeq") #the special AthSequencer that gets run before AthAlgSeq
from DataSelectorAlgs.DataSelectorAlgsConf import OfflineElectronSelectorAlg
mySeq = OfflineElectronSelectorAlg("OfflineElectronSelector")
mySeq.ElectronEtCut = 20.
mySeq.ElectronEtaCut = 2.5
mySeq.OutputLevel = DEBUG
seq += mySeq

from AthenaCommon.AlgSequence import AlgSequence, AthSequencer
job = AlgSequence()

import AthenaPoolCnvSvc.ReadAthenaPool
ServiceMgr.EventSelector.InputCollections = filelist

from RecExConfig.RecFlags import rec
rec.readAOD = True
rec.readRDO = False

from AthenaCommon.GlobalFlags import globalflags
globalflags.DetGeo = 'atlas'
globalflags.DataSource = 'data'

### Trigger Decision Tool
from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
athenaCommonFlags.FilesInput = filelist
from TriggerJobOpts.TriggerFlags import TriggerFlags
TriggerFlags.configurationSourceList=['ds']
from TriggerJobOpts.TriggerConfigGetter import TriggerConfigGetter
cfg = TriggerConfigGetter()



from OutputStreamAthenaPool.MultipleStreamManager import MSMgr
StreamDPD=MSMgr.NewPoolStream("StreamDPD","/dataDisk/Reprocessed/00179939/slimEnhancedBias.pool.root")
StreamDPD.AddMetaDataItem(["IOVMetaDataContainer#*"])
StreamDPD.AddItem( ["EventInfo#*"] )
StreamDPD.AddItem( ["ElectronContainer#ElectronAODCollection","VxContainer#VxPrimaryCandidate","MissingET#MET_RefFinal","egammaContainer#HLT_egamma_Electrons","egDetailContainer#HLT_egamma_Electrons","JetCollection#AntiKt4TopoJets","JetMomentMap#AntiKt4TopoJets"] )
StreamDPD.AcceptAlgs(["OfflineElectronSelector"])
