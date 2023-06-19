
import sys
import os

path = os.getcwd()

sys.path.insert(1,path +'/avx512_gen')
sys.path.insert(1,path + '/avx_gen')

from avx_gen import gen_mipp_avx
from avx512_gen import gen_mipp_avx512
dir = 
/work/dendanil/MIPP/include/avx512
print(path)

for arg in sys.argv:
	if(arg == "gen_mipp_v2.py"):
		continue
	if(arg == "avx2"):
		gen_mipp_avx.gen_mipp_avx()
	elif (arg == "avx512"):
		gen_mipp_avx512.gen_mipp_avx512()
	elif (arg == "all"):
		gen_mipp_avx512.gen_mipp_avx512()
		print("//////////////////////////////////////////////////////////")
		gen_mipp_avx.gen_mipp_avx()
	elif (arg == "--help"):
		print("avx: mipp generator for avx2 simd")
		print("avx512: mipp generator for avx512 simd")
		print("version: mipp version")
	elif (arg == "--version"):
		print("MIPP.V2 version 2023")
	
	else:
		print("Error: unknown argument : {}".format(arg))
		sys.exit(1)