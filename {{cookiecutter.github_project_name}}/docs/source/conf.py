#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import subprocess

on_rtd = os.environ.get('READTHEDOCS', None) == 'True'

if on_rtd:
    subprocess.call('cd ..; doxygen', shell=True)

import sphinx_rtd_theme

html_theme = "sphinx_rtd_theme"

html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]

extensions = ['breathe']
breathe_projects = { '{{cookiecutter.project_name}}': '../xml' }
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
project = '{{cookiecutter.project_name}}'
copyright = '{{cookiecutter.year}}, {{cookiecutter.full_name}}'
author = '{{cookiecutter.full_name}}'


exclude_patterns = []
highlight_language = 'c++'
pygments_style = 'sphinx'
todo_include_todos = False
htmlhelp_basename = '{{cookiecutter.project_name}}_doc'

