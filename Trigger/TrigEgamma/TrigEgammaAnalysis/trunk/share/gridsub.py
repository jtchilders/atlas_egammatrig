config['LCG']['MatchBeforeSubmit'] = True

#myDatasets = ['data10_7TeV.00166658.physics_Egamma.recon.ESD.f295']
#myDatasets = ['data10_7TeV.00166658.physics_Egamma.merge.AOD.f295_m619' ]
#myDatasets = [ 'data10_7TeV.periodI.physics_Egamma.PhysCont.AOD.repro05_v02/' ]
myDatasets = [ 'data10_7TeV.00167776.physics_Egamma.merge.AOD.r1774_p327_p333/' ]
### Set useLCG = True to use LCG, False to use Panda
### The MC is on Panda
useLCG = False

j = Job()
j.application = Athena()
j.application.atlas_dbrelease = 'LATEST' 
j.application.option_file = ['ZeeTagAndProbeAnalysis_joboptions.py' ]
j.name = 'L1Calo example job'
j.application.prepare()
j.inputdata = DQ2Dataset()
j.inputdata.dataset = myDatasets
j.outputdata = DQ2OutputDataset()
j.splitter = DQ2JobSplitter()
j.splitter.numsubjobs = 1500
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

