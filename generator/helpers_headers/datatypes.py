"""
Datatypes Module
Defines all the SIMD datatypes, categories, sets, and cartesian product groupings
used throughout the MIPP generator (headers, tests, and documentation).
"""

# houps test code generation option to do displace
# warning order
all_ldiv = [2]#,4]

all_lmul = [1,2,4,8]
# end houps test code generation option to do displace

cfloat = "float"
cint = "int"
cuint = "uint"

all_categories = [cfloat, cint, cuint]

float64 = cfloat + "64"
float32 = cfloat + "32"
int64 = cint + "64"
int32 = cint + "32"
int16 = cint + "16"
int8 = cint + "8"
uint64 = cuint + "64"
uint32 = cuint + "32"
uint16 = cuint + "16"
uint8 = cuint + "8"

all_float = [float64, float32]
all_int = [int64, int32, int16, int8]
all_uint = [uint64, uint32, uint16, uint8]
all_int_uint = all_int + all_uint
all_datatypes = all_float + all_int_uint
all_64bit = [float64, int64, uint64]
all_32bit = [float32, int32, uint32]
all_16bit = [int16, uint16]
all_8bit = [int8, uint8]
all_defs = []

all_datatypes_cart_prod = []
for dt_ret in all_datatypes:
    for dt_par in all_datatypes:
        new_entry = [dt_par, dt_ret]
        if new_entry not in all_datatypes_cart_prod:
            all_datatypes_cart_prod.append(dt_par + "," + dt_ret)


all_datatypes_cart_prod_except_f64 = []
for dt_ret in all_datatypes:
    if dt_ret != "float64":
        for dt_par in all_datatypes:
            if dt_par != "float64":
                new_entry = [dt_par, dt_ret]
                if new_entry not in all_datatypes_cart_prod_except_f64:
                    all_datatypes_cart_prod_except_f64.append(dt_par + "," + dt_ret)

all_datatypes_cart_prod_inc_f64 = []
for dt_ret in all_datatypes:
    for dt_par in all_datatypes:
        new_entry = [dt_par, dt_ret]
        if new_entry not in all_datatypes_cart_prod_inc_f64:
            if dt_par == "float64" or dt_ret == "float64":
                all_datatypes_cart_prod_inc_f64.append(dt_par + "," + dt_ret)


# First definition of gather will use this 4 simplicity's sake
all_datatypes_idx_pair = []
for type in [cfloat, cint, cuint]:
    for n_bits in [64, 32, 16, 8]:
        if type == cfloat and n_bits in [16, 8]:
            continue
        dt = type + str(n_bits)
        idx = cuint + str(n_bits)
        all_datatypes_idx_pair.append(dt + "," + dt)

avx_datatypes_idx_pair = [
    "float64,float64",
    "float32,float32",
    "int64,int64",
    "int32,int32",
]


same_dt = [
    "float64,float64",
    "float32,float32",
    "int64,int64",
    "int32,int32",
    "uint64,uint64",
    "uint32,uint32",
    "int16,int16",
    "int8,int8",
    "uint16,uint16",
    "uint8,uint8",
]

f2i_dt = [ "float64,int64", "float32,int32" ]
f2u_dt = [ "float64,uint64", "float32,uint32" ]

i2f_dt = [ "int64,float64", "int32,float32"]
i2u_dt = [ "int64,uint64", "int32,uint32", "int16,uint16", "int8,uint8" ]

u2f_dt = [ "uint64,float64", "uint32,float32"]
u2i_dt = [ "uint64,int64", "uint32,int32", "uint16,int16", "uint8,int8" ]

all_datatypes_same_size = same_dt + f2i_dt + f2u_dt + i2f_dt + i2u_dt + u2f_dt + u2i_dt
all_datatypes_same_size_except_f64 = [dt for dt in all_datatypes_same_size if "float64" not in dt]
all_datatypes_same_size_inc_f64 = [dt for dt in all_datatypes_same_size if "float64" in dt]

int_dt_widenning = [ "int32,int64", "int16,int32", "int8,int16" ]
float_dt_widenning = [ "float32,float64" ]
uint_dt_widenning = [ "uint32,uint64", "uint16,uint32", "uint8,uint16" ]

all_datatypes_widenning = int_dt_widenning + float_dt_widenning + uint_dt_widenning
