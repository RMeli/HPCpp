```bash
uv venv
source .venv/bin/activate

uv pip install numpy

cmake -S . -B build -GNinja
cmake --build build

./build/nptest
```
