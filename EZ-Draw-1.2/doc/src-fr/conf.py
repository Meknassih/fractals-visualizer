#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# EZ-Draw documentation build configuration file, created by
# sphinx-quickstart on Fri Feb 28 10:43:37 2014.
#
# This file is execfile()d with the current directory set to its
# containing dir.
#
# Note that not all possible configuration values are present in this
# autogenerated file.
#
# All configuration values have a default; values that are commented out
# serve to show the default.

import sys
import os

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#sys.path.insert(0, os.path.abspath('.'))


# Exec multilingual common configuration
exec(open("../share/common-conf.py").read())


# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#language = None
language = 'fr'

# The name for this set of Sphinx documents.  If None, it defaults to
# "<project> v<release> documentation".
html_title = "Documentation de EZ-Draw 1.2"

# A shorter title for the navigation bar.  Default is the same as html_title.
html_short_title = 'Documentation'


# A string of reStructuredText that will be included at the end of every source 
# file that is read.
rst_epilog += """

.. |c-chemin-EZ-Draw-x.y| replace:: c:\\\\chemin\\\\EZ-Draw-{ver}
.. |pre-c-chemin-EZ-Draw-x.y| replace:: ``c:\\chemin\\EZ-Draw-{ver}``

""".format(ver=ez_version)

