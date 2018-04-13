# ![xleaflet](http://quantstack.net/assets/images/xleaflet.svg)

[![Join the Gitter Chat](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/QuantStack/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

C++ backend for the jupyter-leaflet map visualization library

**xleaflet is an early developer preview, and is not suitable for general usage yet. Features and implementation are subject to change.**

## Usage

![xleaflet screencast](xleaflet.gif)

## Installation

We provide a package for the conda package manager.

- Installing `xleaflet` and the C++ kernel

```bash
conda install xeus-cling xleaflet -c QuantStack -c conda-forge
```

Then, the front-end extension must be installed for either the classic notebook or JupyterLab.

- Installing the extensions for the classic notebook

```
conda install widgetsnbextension -c conda-forge
conda install ipyleaflet -c conda-forge
```

- Installing the JupyterLab extension

```
jupyter labextension install @jupyter-widgets/jupyterlab-manager
jupyter labextension install jupyter-leaflet
```

## Installation from sources

Or you can directly install it from the sources if you have all the dependencies already installed:

```bash
cmake -D CMAKE_INSTALL_PREFIX=your_install_prefix
make install
```

## Dependencies

All the dependencies of xleaflet are available for the conda package manager.

| `xleaflet` | `xwidgets`  |  `xeus`         |
|------------|-------------|-----------------|
|  master    |   ~0.8.2    |  >=0.11.0,<0.12 |

## License

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the [LICENSE](LICENSE) file for details.
