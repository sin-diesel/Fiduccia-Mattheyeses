# Fiduccia-Mattheyses algorithm

This algorithm's purpose is to split hypergraph into two parts. Works for Linux and Windows.

### Build

```
cd Fiduccia
cmake -S . -B build
cmake --build build
```

### Run

> Windows
```
.\build\Fiduccia.exe <benchmark_path>

Without compilation
.\bin\Fiduccia.exe <benchmark_path>
```
> Linux
```
./build/Fiduccia <benchmark_path>

Without compilation
./bin/Fiduccia <benchmark_path>
```