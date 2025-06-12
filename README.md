# ![xleaflet](docs/source/xleaflet.svg)

[![GithubActions](https://github.com/jupyter-xeus/xleaflet/actions/workflows/main.yml/badge.svg)](https://github.com/jupyter-xeus/xleaflet/actions/workflows/main.yml)

[![Documentation](http://readthedocs.org/projects/xleaflet/badge/?version=latest)](https://xleaflet.readthedocs.io/en/latest/?badge=latest)
[![Binder](https://img.shields.io/badge/launch-binder-brightgreen.svg)](https://mybinder.org/v2/gh/jupyter-xeus/xleaflet/stable?filepath=notebooks)
[![Join the Gitter Chat](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/QuantStack/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

C++ backend for the jupyter-leaflet map visualization library

## Usage

Selecting a base layer for a map:

![Basemap Screencast](basemap.gif)

Loading a geojson dataset:

![GeoJSON Screencast](geojson.gif)

Using the splitmap control:

![Splitmap Screencast](splitmap.gif)

Displaying velocity data on the top of a map:

![Velocity Screencast](velocity.gif)

## Installation

We provide a package for the mamba (or conda) package manager.

- Installing `xleaflet` and the C++ kernel

```bash
mamba install xeus-cling xleaflet -c conda-forge
```

Then, the front-end extension must be installed for either the classic notebook or JupyterLab.

- Installing the extensions for the classic notebook

```
mamba install widgetsnbextension -c conda-forge
mamba install ipyleaflet -c conda-forge
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

## Trying it online

To try out xleaflet interactively in your web browser, just click on the binder
link:

[![Binder](docs/source/binder-logo.svg)](https://mybinder.org/v2/gh/jupyter-xeus/xleaflet/stable?filepath=notebooks/)

## Documentation

To get started with using `xleaflet`, check out the full documentation

http://xleaflet.readthedocs.io/

## License

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the [LICENSE](LICENSE) file for details.
