# docpp

![action](https://github.com/speediegq/docpp/actions/workflows/cmake-multi-platform.yml/badge.svg)

C++17 library for generating HTML, CSS and SGML-like documents.

## Features

- HTML and CSS document generation and deserialization
- Sensible indentation for pretty-formatting.
- Modern C++ API
- No dependencies, other than the standard library
- Windows, macOS, Linux and *BSD support
- LGPL license

## Not yet implemented

- HTML/CSS serialization (parsing from e.g. file)

## Installation

To install the library, you can utilize the provided CMakeLists.txt file:

```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
cmake --build .
cmake --install . --prefix /usr
```

This will install the library to /usr/lib and the headers to /usr/include/docpp.

```sh
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
cmake --build .
makepkg -si
```

## Usage

Just include the appropriate headers in your project and link against the library. 
If you are not sure which header(s) are appropriate, you can include all of them by 
including docpp.hpp. Examples can be found in the examples directory.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to contribute to this project.

## License

This project is licensed under the GNU Lesser General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## Code of Conduct

None. Just don't blow up my house. And, don't ask me to rewrite it in Rust.
