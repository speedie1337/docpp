# docpp

![action](https://github.com/speediegq/docpp/actions/workflows/cmake-multi-platform.yml/badge.svg)

Small C++ library for generating XML, HTML and CSS.

## Features

- HTML, CSS and XML document generation and deserialization
- Sensible indentation for pretty-formatting.
- Modern C++ API
- No dependencies, other than the standard library
- Windows, macOS, Linux and *BSD support
- LGPL license

## Not yet implemented

- HTML/XML/CSS serialization (parsing from e.g. file)

## Installation

To install the library, you can utilize the provided CMakeLists.txt file:

```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
cmake --build .
cmake --install . --prefix /usr
```

## Usage

Just include docpp.hpp in your project and link against the library. Examples can be found in the examples directory.

## License

This project is licensed under the GNU Lesser General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## Code of Conduct

None. Just don't blow up my house. And, don't ask me to rewrite it in Rust.
