# MyIntrinsics++ (MIPP)

![](docs/assets/images/mipp.jpg)

**TODO**

## Documentation

### MkDocs Intallation

```bash
sudo apt install python3 python3-pip python3-venv
python3 -m venv .venv
source .venv/bin/activate
pip3 install -r docs/requirements.txt
deactivate
```

### MkDocs Generation for Development

To generate the documentation, just do:

```bash
source .venv/bin/activate
cd generator
./gen_mipp_docs.py
cd ..
mkdocs serve
```

And then the documentation will be browsable there : http://127.0.0.1:8000/

### MkDocs Generation for Production

To generate the documentation, just do:

```bash
mkdocs build
```

The latest will produce a new site directory that contains the static and
generated website.
