# MIPP Generator

The generator is written in Python 3 and relies on Jinja 2.

Install Python, set a virtual environement and install the requirements 
(Jinja 2): 
```bash
sudo apt install python3 python3-pip python3-venv
python3 -m venv .venv
source .venv/bin/activate
pip3 install -r requirements.txt
deactivate
```

## Generate MIPP Headers

```bash
source .venv/bin/activate
./gen_mipp_headers.py
```

## Generate MIPP Tests

```bash
source .venv/bin/activate
./gen_mipp_tests.py
```


## Generate MIPP Documentation

```bash
source .venv/bin/activate
./gen_mipp_infos.py
```
