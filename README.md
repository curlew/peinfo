<div align="center">

# peinfo
[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/curlew/peinfo/cmake.yml?logo=github&style=flat-square)](https://github.com/curlew/peinfo/actions/workflows/cmake.yml)
[![License](https://img.shields.io/github/license/curlew/peinfo?style=flat-square)](https://github.com/curlew/peinfo/blob/main/LICENSE)

</div>

## Usage
```
Usage: peinfo.exe [options] FILE
View headers and sections of Portable Executable files.

Options:
  -f  Display file header
  -o  Display optional header
  -s  Display section table
  -i  Display import table
  -e  Display export table
  -h  Display this help message and exit

If no options are specified, display all available information.
```

## Building
```
PS> cmake -B build
PS> cmake --build build --config Release
```
