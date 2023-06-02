data_types = {
    'float64_t': 'float64',
    'float32_t': 'float32',
    'int64_t': 'int64',
    'int32_t': 'int32',
    'int16_t': 'int16',
    'int8_t': 'int8',
    'uint64_t': 'uint64',
    'uint32_t': 'uint32',
    'uint16_t': 'uint16',
    'uint8_t': 'uint8'
}
functions = []

for data_type, dtype in data_types.items():
    for m in [1, 2, 4, 8]:
        function_signature = f"void storeu({data_type} *mem_addr, const rvd<{dtype},{m}> rvd)"
        function_call = f"mipp_storeu_{dtype}_m{m}(mem_addr, rvd)"
        function_definition = f"{function_signature} {{ {function_call}; }}"
        functions.append(function_definition)

generated_code = '\n'.join(functions)

print(generated_code)
