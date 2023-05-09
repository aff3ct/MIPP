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

}

implems_emu = {
		"set0":[
		{ "datatypes": [float64], "template": tpl_implem_emu512["set0-f64"], "if": "defined(__MIC__) || defined(__KNCNI__)"},
		{ "datatypes": [float32], "template": tpl_implem_emu512["set0-f32"],"if": "defined(__MIC__) || defined(__KNCNI__)"},
		{ "datatypes": [int32], "template": tpl_implem_emu512["msb-32"],"if": "defined(__MIC__) || defined(__KNCNI__)"},],

}