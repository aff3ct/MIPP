# MIPP Generator

The MIPP headers, unit tests and reference pages are generated from the JSON
files of this directory by Python 3 scripts (Jinja2, jsonschema).

```bash
python3 -m venv .venv
source .venv/bin/activate
pip3 install -r requirements.txt

./gen_mipp_headers.py   # headers in ../include/
./gen_mipp_tests.py     # unit tests in ../tests/src/
./gen_mipp_docs.py      # reference pages in ../docs/
```

All the scripts are run from this directory. The options, the workflow and the
tutorials (add a function, an implementation or an ISA) are in the Developer
Guide: https://aff3ct.github.io/MIPP/developer/setup/
