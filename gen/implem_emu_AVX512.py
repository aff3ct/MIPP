from tools import *

tpl_implem_emu512 = {
	
		"set0-f64" : { "format": "long", "code":
	"""  return %set1<c:float|b:tp,tp>%(0.0); """
		},
		"set0-f32" : { "format": "long", "code":
	"""  return %set1<c:float|b:tp,tp>%(0.f); """
		},
		"set0-32" : { "format": "long", "code":
	"""  return %set1<c:float|b:tp,tp>%(0); """
		},
		"set0_k"   : { "format": "short", "code": 
	""" %r<c:int|b:32>% r32 = %set1<c:int|b:32>%(0);
 	    %m<c:int|b:32>% m32 = %tomsk<c:int|b:32>%(r32);
  	    return _mm512_kxor(m32, m32);""" 
  	    }, 
	
		"set0":[
		{ "datatypes": [float64] , "template": tpl_implem_emu512["set0-f64"] , "if": "defined(__MIC__) || defined(__KNCNI__)"} ,
		{ "datatypes": [float32] , "template": tpl_implem_emu512["set0-f32"] , "if": "defined(__MIC__) || defined(__KNCNI__)"} ,
		{ "datatypes": [int32]   , "template": tpl_implem_emu512["set0-32"]  , "if": "defined(__MIC__) || defined(__KNCNI__)"} , ] ,
		
		"set0_k": [
		{ "datatypes": [int32]   , "template": tpl_implem_emu512["set0_k"]} , ] ,

}