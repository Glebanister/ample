#!/usr/bin/env python3

# -*- coding: utf-8 -*-
"""Ample project manager

This designed to manage Ample projects.
Ample is a game engine and framework: https://github.com/Glebanister/ample

Current feautures:
    * ample init [project_name]                 - init ample project in current directory
    * ample build {--debug, --release, --clear} - build ample project
    * ample run                                 - run ample project

This project manager suggests that your project structure will be like:
    ├── build                       - cmake's build files
    ├── CMakeLists.txt              - automatically generated file for building your project
    ├── include                     - contains listed headers and your custom ones
    │   └── [activity_name].h
    └── src                         - contains listed source files and your custom ones
        ├── [main_file].cpp
        └── [activity_name].cpp

After 'ample init [project_name]' ample will genetate folder '.ample' (hidden), it contains
config.json file. This is actual settings of your project.
{
    "ready": true,
    "project_name": "MyGame",       - your project name
    "activity_name": "MyGame",      - name of main activity. I don't reccomend you to
                                      change it to other, otherwise you have to
                                      change automatilcally generated
                                      [source_dir]/[activity_name].cpp
                                      file name to actual.
    "include_dir": "include",       - headers path. If changed, you have to rename your
                                      include path to actual one.
    "source_dir": "src",            - same, but sources
    "main_file": "main",            - called to run your project. The file itself generates
                                      automatically, so you can't actually change it.
    "window_name": "MyGame",        - name of window, that opens on your game borned.
    "window_w": 1920,               - width of window
    "window_h": 1080,               - height
    "fullscreen": false,            - if fullscreen
    "resizable": true,              - if resizable
    "borderless": false,            - if borderless
    "cxx_flags": "-std=c++17",      - compilation flags, you may add some.
    "sources": [                    - all your sources. When you add one,
                                      you HAVE TO register it here.
        "src/main.cpp",
        "src/MyGame.cpp"
    ]
}

So, once you initialized your project, then you just implement your game in [activity_name]

There is no engine documentation so far, work is in progress.

TODO:
    * Fix pylint: disable=too-many-instance-attributes by wrapping members into dict
"""

import argparse
import os
import sys
import json


class AmpleProject:  # pylint: disable=too-many-instance-attributes
    """
    Representation of your project
    """

    def __init__(self):
        self.ready = False
        self.ready = None
        self.project_name = None
        self.activity_name = None
        self.include_dir = None
        self.source_dir = None
        self.main_file = None
        self.window_name = None
        self.window_w = None
        self.window_h = None
        self.fullscreen = None
        self.resizable = None
        self.borderless = None
        self.cxx_flags = None
        self.sources = None
        if os.path.exists(f'.ample'):
            self.__from_json()

    def __from_json(self):
        with open('.ample/config.json') as config_file:
            data = json.load(config_file)
            self.ready = data['ready']
            self.project_name = data['project_name']
            self.activity_name = data['activity_name']
            self.include_dir = data['include_dir']
            self.source_dir = data['source_dir']
            self.main_file = data['main_file']
            self.window_name = data['window_name']
            self.window_w = data['window_w']
            self.window_h = data['window_h']
            self.fullscreen = data['fullscreen']
            self.resizable = data['resizable']
            self.borderless = data['borderless']
            self.cxx_flags = data['cxx_flags']
            self.sources = data['sources']

    def __to_json(self):
        # dump project to .json
        with open('.ample/config.json', 'w') as config_file:
            json.dump(self.__dict__, config_file)

    def init(self,         # pylint: disable=too-many-arguments
             project_name,
             activity_name,
             include_dir,
             source_dir,
             main_file,
             window_name,
             window_w,
             window_h,
             fullscreen,
             resizable,
             borderless,
             cxx_flags):
        """init project in current directory"""

        if os.path.exists(f'.ample'):
            raise EnvironmentError('current directory is ample already')

        self.project_name = project_name
        self.activity_name = project_name
        self.include_dir = include_dir
        self.source_dir = source_dir
        self.main_file = main_file
        self.window_name = window_name
        self.window_w = window_w
        self.window_h = window_h
        self.fullscreen = fullscreen
        self.resizable = resizable
        self.borderless = borderless
        self.cxx_flags = cxx_flags
        self.sources = [f'{source_dir}/{main_file}.cpp',
                        f'{source_dir}/{activity_name}.cpp']

        try:
            os.mkdir(f'{include_dir}')
            os.mkdir(f'{source_dir}')
            os.mkdir(f'build')
            os.mkdir(f'.ample')
        except FileExistsError:
            raise EnvironmentError('file already exists')
        except Exception:
            raise EnvironmentError('can not init ample directory here')

        self.__write_file_from_template(
            f'{include_dir}/{project_name}.h',
            '../templates/mainActivity.h.template')
        self.__write_file_from_template(
            f'{source_dir}/{project_name}.cpp',
            '../templates/mainActivity.cpp.template')
        self.__write_file_from_template(
            f'{source_dir}/{main_file}.cpp',
            '../templates/main.cpp.template')
        self.__write_file_from_template(
            f'CMakeLists.txt',
            '../templates/CMakeLists.txt.template')

        self.ready = True
        self.__to_json()

    def build(self, build_type):
        """ build project """

        if not self.ready:
            raise EnvironmentError('not an ample directory')

        if build_type == 'clean':
            if os.system('rm -rf build/*'):
                raise EnvironmentError('build unsuccessfull')
            return

        build_flags = ''
        if build_type == 'debug':
            build_flags += '-DCMAKE_BUILD_TYPE=Debug'
        if build_type == 'release':
            build_flags += '-DCMAKE_BUILD_TYPE=Release'

        self.__write_file_from_template(
            f'{self.source_dir}/{self.main_file}.cpp',
            '../templates/main.cpp.template')
        self.__write_file_from_template(
            f'CMakeLists.txt',
            '../templates/CMakeLists.txt.template')
        try:
            os.chdir('build')
        except OSError:
            os.mkdir('build')
            os.chdir('build')
        if os.system(f'cmake {build_flags} ..') != 0:
            raise EnvironmentError('build unsuccessfull')
        if os.system(f'cmake --build .') != 0:
            raise EnvironmentError('build unsuccessfull')

    def run(self):
        """ run project """

        if not self.ready:
            raise EnvironmentError('not an ample directory')
        if not os.path.isfile(f'build/{self.project_name}'):
            raise EnvironmentError('build not ready')
        os.system(f'build/{self.project_name}')

    def __write_file_from_template(self, out_file, template_file):
        out = open(out_file, 'w')
        try:
            template = open(template_file, 'r')
        except FileNotFoundError:
            raise EnvironmentError(
                f'could not find template file {template_file}')

        window_param = 'os::winmode::UNDEFINED_MODE'
        if self.fullscreen:
            window_param += ' | os::winmode::FULLSCREEN'
        if self.resizable:
            window_param += ' | os::winmode::RESIZABLE'
        if self.borderless:
            window_param += ' | os::winmode::BORDERLESS'

        for line in template.readlines():
            out.write(line.replace('$project_name', self.project_name)
                      .replace('$activity_name', self.activity_name)
                      .replace('$window_name', self.window_name)
                      .replace('$window_w', str(self.window_w))
                      .replace('$window_h', str(self.window_h))
                      .replace('$window_param', window_param)
                      .replace('$main', self.main_file)
                      .replace('$include_dir', self.include_dir)
                      .replace('$source_dir', self.source_dir)
                      .replace('$cxx_flags', self.cxx_flags)
                      .replace('$sources', '\n'.join(self.sources))
                     )
        out.close()
        template.close()


def init_handler(project_name):
    """ initialization command handler """

    project = AmpleProject()
    if os.listdir('.'):
        user_resp = ''
        while user_resp not in ['y', 'n']:
            user_resp = input(
                'Current directory is not empty. Continue? [y/n] ').lower()
        if user_resp == 'n':
            return
    try:
        project.init(project_name=project_name,
                     activity_name=project_name,
                     include_dir='include',
                     source_dir='src',
                     main_file='main',
                     window_name=project_name,
                     window_w=1920, window_h=1080,
                     fullscreen=False,
                     resizable=True,
                     borderless=False,
                     cxx_flags='-std=c++17')
    except EnvironmentError as exc:
        print(f'Error: {exc.args[0]}')
        sys.exit(1)
    else:
        print('Ample directory initialized successfully')


def build_handler(build_type):
    """ building command handler """

    project = AmpleProject()
    try:
        project.build(build_type)
    except EnvironmentError as exc:
        print(f'Error: {exc.args[0]}')
        sys.exit(1)
    else:
        print('Build completed')


def run_handler():
    """ running command handler """

    project = AmpleProject()
    try:
        project.run()
    except EnvironmentError as exc:
        print(f'Error: {exc.args[0]}')


def main(args_str):
    """ Entry point """
    parser = argparse.ArgumentParser(
        description='ample project manager')

    subparsers = parser.add_subparsers()

    init_parser = subparsers.add_parser(
        'init', help='init ample in current directory')
    init_parser.add_argument(
        'init_project_name',
        help='name of your project')
    init_parser.set_defaults(init=True)
    parser.set_defaults(init=False)

    build_parser = subparsers.add_parser('build', help='build ample project')
    build_parser.add_argument('-d', '--debug',
                              dest='build_type',
                              action='store_const',
                              const='debug',
                              default='debug',
                              help='build type: debug')
    build_parser.add_argument('-r', '--release',
                              dest='build_type',
                              action='store_const',
                              const='release',
                              help='build type: release')
    build_parser.add_argument('-c', '--clean',
                              dest='build_type',
                              action='store_const',
                              const='clean',
                              help='build type: clear')
    build_parser.set_defaults(build=True)
    parser.set_defaults(build=False)

    run_parcer = subparsers.add_parser('run', help='execute ample project')
    run_parcer.set_defaults(run=True)
    parser.set_defaults(run=False)

    args = parser.parse_args(args_str)

    if args.init:
        init_handler(args.init_project_name)

    if args.build:
        build_handler(args.build_type)

    if args.run:
        run_handler()


if __name__ == '__main__':
    main(sys.argv[1:])
