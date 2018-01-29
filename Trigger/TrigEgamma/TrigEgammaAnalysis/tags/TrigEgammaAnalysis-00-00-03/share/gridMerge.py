# hadd all files in the list
# Assume file list is in input.txt

import os, sys
import commands
import threading
import optparse
import ROOT

# ------------------------------------------------
class HaddThread(threading.Thread):
    """A subclass of threading.Thread, with a kill() method."""
    
    def __init__(self, flist, outf) :
        threading.Thread.__init__(self)
        self.killed = False
        self._flist = flist
        self._outf = outf
        self._complete = False
        self._error = False         
        
    def start(self):
        """Start the thread."""
        self.__run_backup = self.run
        self.run = self.__run # Force the Thread to install our trace.
        threading.Thread.start(self)
        
    def __run(self):
        """Hacked run function, which installs the
        trace."""
        sys.settrace(self.globaltrace)
        self.__run_backup()
        self.run = self.__run_backup
        
    def run(self):
        "Run hadd over this list           "

        # Merge the given list to one file using hadd
        cmd_str = "hadd %s %s" % (self._outf, ' '.join( self._flist ) )

        print "Running: " + cmd_str
        rc, out = commands.getstatusoutput( cmd_str )

        # check all is well
        if (rc != 0) or not os.path.exists(self._outf):
            print "Error running hadd: %s" % out
            self._error = True

        self._complete = True
        
    def globaltrace(self, frame, why, arg):
        if why == 'call':
            return self.localtrace
        else:
            return None

    def localtrace(self, frame, why, arg):
        if self.killed:
            if why == 'line':
                raise SystemExit()
            return self.localtrace
        
    def kill(self):
        self.killed = True

def mergeLargeFileList( flist, num_per_merge, out_dir ):
    # merge the list in groups of 'num' files
    new_list = []
    num = 0
    os.mkdir(out_dir)
    error = False
    
    # Memory use scales with file size rather than # of files
    # decide how many threads to use
    try:
        tf = ROOT.TFile(flist[0])
        size = tf.GetSize()
        tf.Close()
        if (size > 1000000000):    # 1GB
            print "ERROR: Size of %s is too big (%d). Stopping." % (flist[0], size)
            sys.exit(-1)
            
        num_threads = 1000000000/(size*25)
        
    except:
        print "Unable to open ROOT file %s to get size - forcing 1 thread" % flist[0]
        num_threads = 1        

    if num_threads < 1:
        num_threads = 1

    if num_threads > 20:
        num_threads = 20
        
    threads = []

    print "Splitting across a max of %d threads..." % num_threads
    
    while True:
        
        if len(flist) > 0 and len(threads) < num_threads:
            next_list = flist[:num_per_merge]
            flist = flist[num_per_merge:]
            num += 1
            
            print "Creating next merged file (%d)" % num
            next_out = "%s/next_out_%d.root" % (out_dir, num)

            th = HaddThread( next_list, next_out )
            threads.append( th )
            th.start()

        for th in threads:
            if th._error:
                print "ERROR with hadd. Stopping."
                error = True
                
            if th._complete:
                new_list.append(th._outf)
                threads.remove(th)
                break

        if len(flist) == 0 and len(threads) == 0:
             break
        
    if error:
        sys.exit(-1)
    
    return new_list

# ---------------------------------------

if __name__ == '__main__':
    
    usage = """
    python gridMerge.py -i [INPUTFILE] -o [OUTPUTFILE] -n [NUMFILESPERMERGE]
    """

    p = optparse.OptionParser(usage=usage)
    p.add_option('--in', '-i', action='store', type='string', dest='infile', help='File list to process')
    p.add_option('--out', '-o', action='store', type='string', dest='outfile', help='Output file')
    p.add_option('--num', '-n', action='store', type='int', dest='num', help='Number of files to combine per step (time scales with this)')
    opt, args = p.parse_args()

    if not opt.infile:
        p.error("No input file specified")

    if not opt.outfile:
        p.error("No output file specified")

    if not opt.num:
        p.error("No Number of files specified")
    
    fulllist = open(opt.infile, 'r').readlines()
    next_list = []
    num = 0
    fulllist2 = []
    
    for f in fulllist:
        fulllist2.append(f.strip())

    old_list = fulllist2
    
    while len(old_list) > 1:
        print "-------   Running pass %d:" % num
        old_list = mergeLargeFileList( old_list, opt.num, 'pass_%d' % num )
        num += 1
        
    os.rename(old_list[0], opt.outfile)
