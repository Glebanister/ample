#!/usr/bin/env python3
import argparse
import os
import sys
import json
from collections import namedtuple


'''
TODO:
    - command: run
    - command: source
'''


class AmpleProject:
    def __init__(self):
        self.ready = False
        if os.path.exists(f'.ample'):
            self.__from_json()

    def __from_json(self):
        data = {}
        with open('.ample/config.json') as f:
            data = json.load(f)
        try:
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
        except KeyError as exc:
            raise Exception(f'{exc.args[0]} not found in .ample/config.json')
        self.ready = True

    def __to_json(self):
        with open('.ample/config.json', 'w') as fp:
            json.dump(self.__dict__, fp)

    def init(self,
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
             borderless):

        if os.path.exists(f'.ample'):
            raise Exception('current directory is ample already')

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

        try:
            os.mkdir(f'{include_dir}')
            os.mkdir(f'{source_dir}')
            os.mkdir(f'build')
            os.mkdir(f'.ample')
        except FileExistsError:
            raise Exception('file already exists')
        except Exception as e:
            raise Exception('can not init ample directory here')

        self.__write_file_from_template(
            f'{include_dir}/{project_name}.h', '../templates/mainActivity.h.template')
        self.__write_file_from_template(
            f'{source_dir}/{project_name}.cpp', '../templates/mainActivity.cpp.template')
        self.__write_file_from_template(
            f'{source_dir}/{main_file}.cpp', '../templates/main.cpp.template')
        self.__write_file_from_template(
            f'CMakeLists.txt', '../templates/CMakeLists.txt.template')

        self.__to_json()

    def build(self, type):
        if not self.ready:
            raise Exception('not an ample directory')
        self.__write_file_from_template(
            f'{self.source_dir}/{self.main_file}.cpp', '../templates/main.cpp.template')
        self.__write_file_from_template(
            f'CMakeLists.txt', '../templates/CMakeLists.txt.template')
        try:
            os.chdir('build')
        except Exception:
            os.mkdir('build')
            os.chdir('build')
        if os.system('cmake .. && cmake --build .') != 0:
            raise Exception('build unsuccessfull')

    def run(self):
        if not self.ready:
            raise Exception('not an ample directory')
        if not os.path.isfile(f'build/{self.project_name}'):
            raise Exception('build not ready')
        os.system(f'build/{self.project_name}')

    def __write_file_from_template(self, out_file, template_file):
        out = open(out_file, 'w')
        try:
            template = open(template_file, 'r')
        except FileNotFoundError:
            raise Exception(f'could not find template file {template_file}')

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
                          .replace('$source_dir', self.source_dir))
        out.close()
        template.close()


def main(args_str):
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
    build_parser.add_argument('--debug', dest='build_type',
                              action='store_const', const='debug', default='debug', help='build type: debug')
    build_parser.add_argument('--release', dest='build_type',
                              action='store_const', const='release', help='build type: release')
    build_parser.set_defaults(build=True)
    parser.set_defaults(build=False)

    run_parcer = subparsers.add_parser('run', help='execute ample project')
    run_parcer.set_defaults(run=True)
    parser.set_defaults(run=False)

    args = parser.parse_args(args_str)
    project = AmpleProject()

    if args.init:
        if os.listdir('.'):
            user_resp = ''
            while user_resp not in ['y', 'n']:
                user_resp = input(
                    'Current directory is not empty. Continue? [y/n] ').lower()
            if user_resp == 'n':
                return
        try:
            project.init(project_name=args.init_project_name,
                         activity_name=args.init_project_name,
                         include_dir='include',
                         source_dir='src',
                         main_file='main',
                         window_name=args.init_project_name,
                         window_w=1920, window_h=1080,
                         fullscreen=False,
                         resizable=True,
                         borderless=False)
        except Exception as exc:
            print(f'Error: {exc.args[0]}')
            exit(1)
        else:
            print('Ample directory initialized successfully')

    if args.build:
        try:
            project.build(args.build_type)
        except Exception as exc:
            print(f'Error: {exc.args[0]}')
            exit(1)
        else:
            print('Build completed')

    if args.run:
        try:
            project.run()
        except Exception as exc:
            print(f'Error: {exc.args[0]}')


if __name__ == '__main__':
    main(sys.argv[1:])
