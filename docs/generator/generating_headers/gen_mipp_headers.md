# Generating MIPP Headers

The `gen_mipp_headers.py` is a "glue" script that you run to generate every header in the MIPP library. 

What it does is : 

- create directories for the MIPP headers. 
- calls the `gen_mipp_isa()` function for every ISA. 
- calls the `generate_mipp_h()` function
- calls the `generate_c_interface()` function for each ISA
- calls the ` generate_cpp()` function 
- calls the ` generate_cpp_object()` function 

Once the script is done, you should be able to include MIPP ! 

TODO : link to relevant functions documentation, link to README to explain how to run the script