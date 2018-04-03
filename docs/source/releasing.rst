.. Copyright (c) 2018, Johan Mabille and Sylvain Corlay, and Wolf Vollprecht

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Releasing xleaflet
==================

Releasing a new version
-----------------------

From the master branch of xleaflet

- Make sure that you are in sync with the master branch of the upstream remote.
- In file ``xleaflet_config.hpp``, set the macros for ``XLEAFLET_VERSION_MAJOR``, ``XLEAFLET_VERSION_MINOR`` and ``XLEAFLET_VERSION_PATCH`` to the desired values.
- Update the readme file w.r.t. dependencies on xleaflet
- Stage the changes (``git add``), commit the changes (``git commit``) and add a tag of the form ``Major.minor.patch``. It is important to not add any other content to the tag name.
- Push the new commit and tag to the main repository. (``git push``, and ``git push --tags``)
