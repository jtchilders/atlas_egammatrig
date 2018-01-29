j = Job()

j.application = Athena()

j.application.atlas_exetype = 'EXE'
j.application.option_file = 'python gridMerge.py -i input.txt -o out.root -n 20'
j.application.prepare()   # make sure gridMerge.py is in your working dir

j.inputdata = DQ2Dataset()
j.inputdata.dataset = 'user.childers.20110217153609.100/'
j.inputdata.exclude_pattern = ['*.log.tgz.*']

j.outputdata = DQ2OutputDataset()
j.outputdata.outputdata = ['out.root']

j.splitter = DQ2JobSplitter()
j.splitter.numsubjobs = 1

j.backend = Panda()
j.backend.requirements.cloud = 'DE'
j.submit()
