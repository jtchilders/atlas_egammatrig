config['LCG']['MatchBeforeSubmit'] = True

#myDatasets = ['data10_7TeV.00166658.physics_Egamma.recon.ESD.f295']
#myDatasets = ['data10_7TeV.00166658.physics_Egamma.merge.AOD.f295_m619' ]
myDatasets = [ 'data10_7TeV.00167776.physics_Egamma.merge.AOD.f299_m639' ]
### Set useLCG = True to use LCG, False to use Panda
### The MC is on Panda
useLCG = False

j = Job()
j.application = Athena()
#j.application.atlas_dbrelease = 'ddo.000001.Atlas.Ideal.DBRelease.v100701:DBRelease-10.7.1.tar.gz' 
j.application.option_file = ['TRTAnalysis_joboptions.py' ]
j.name = 'L1Calo example job'
j.application.prepare()
j.inputdata = DQ2Dataset()
j.inputdata.dataset = myDatasets
#j.inputdata.exclude_pattern = 
['*._lb*-lb*.1','*._lb01*.1','*._lb00*.1','*._lb03*.1','*._lb021*.1','*._lb022*.1','*._lb023*.1','*._lb024*.1','*._lb025*.1','*._lb026*.1','*._lb027*.1','*._lb028*.1','*._lb029*.1']
j.outputdata = DQ2OutputDataset()
j.splitter = DQ2JobSplitter()
j.splitter.numsubjobs = 700
j.merger = AthenaOutputMerger()

if useLCG:
  j.application.atlas_release = '15.6.12'
  j.outputdata.outputdata = ['output.root' ]
  j.backend = LCG()
  j.backend.requirements.cloud = 'DE'
  j.submit()

if not useLCG:
  j.application.athena_compile = False
  j.backend = Panda()
  j.backend.requirements.anyCloud = False
  j.backend.requirements.cloud = 'DE'
  j.submit()

