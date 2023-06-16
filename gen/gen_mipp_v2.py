
import sys

from gen_mipp_avx import  *
from gen_mipp_avx512 import  *




for arg in sys.argv:
	if(arg == "gen_mipp_v2.py"):
		continue
	if(arg == "avx2"):
		gen_mipp_avx()
	elif (arg == "avx512"):
		gen_mipp_avx512()
	# ajouter un argument avx2 & avx512 & sve 
	elif (arg == "--help"):
		print("avx: mipp generator for avx2 simd")
		print("avx512: mipp generator for avx512 simd")
		print("version: mipp version")
	elif (arg == "--version"):
		print("MIPP.V2 version 2023")
	else:
		print("Error: unknown argument : {}".format(arg))
		sys.exit(1)