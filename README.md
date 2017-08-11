# cpp-tools
General tools written in C++

The project structure here was chosen to follow the Unix Filesystem Hierarchy
Standard [FHS](https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html).

- bin - Generated executable files.
- build - Object files generated from source.
- include - Header files for corresponding project source code files.
- lib - Compiled library files from project and third party (vendor) source.
- share - Shared data (architecture-independent), includes documentation.
- src - Project source code.
- test - Testing files for source code.
- vendor - Third party (non standard) libraries source code (git submodules).
