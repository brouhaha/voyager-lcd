# Copyright 2023 Eric Smith
# SPDX-License-Identifier: GPL-3.0-only

import functools
import itertools
import os

import SCons.Builder

def chunk(it, size):
    it = iter(it)
    return iter(lambda: tuple(itertools.islice(it, size)), ())

def otf_file_to_h_file(otf_fn, h_fn, t = 'uint8_t'):
    array_name = otf_fn.replace('-', '_').replace('.', '_')
    with open(otf_fn, 'rb') as f:
        data = f.read()
    with open(h_fn, 'w') as hf:
        hf_print = functools.partial(print, file = hf, sep = '')
        hf_print(f'#include <stdint.h>')
        hf_print(f'extern const {t} {array_name}[{len(data)}];')
                     
def otf_file_to_c_file(otf_fn, c_fn, t = 'uint8_t'):
    h_fn = os.path.splitext(c_fn)[0] + '.h'
    array_name = otf_fn.replace('-', '_').replace('.', '_')
    with open(otf_fn, 'rb') as f:
        data = f.read()
    with open(c_fn, 'w') as cf:
        cf_print = functools.partial(print, file = cf, sep = '')
        cf_print(f'#include <stdint.h>')
        cf_print(f'#include "{h_fn}"')
        cf_print(f'const {t} {array_name}[{len(data)}] =')
        cf_print('{')
        for group in chunk(data, 12):
            cf_print('  ', ', '.join([f'0x{b:02x}' for b in group]), ',')
        cf_print('};')
                     
def otf_to_h_action(target, source, env):
    print(f'  otf_to_h_action, {target=}, {source=}')
    otf_file_to_h_file(source[0].name, target[0].name)

def otf_to_c_action(target, source, env):
    print(f'  otf_to_c_action, {target=}, {source=}')
    otf_file_to_c_file(source[0].name, target[0].name)

otf_to_h_builder = SCons.Builder.Builder(action = otf_to_h_action,
                                         suffix = '.h',
                                         src_suffix = '.otf')

otf_to_c_builder = SCons.Builder.Builder(action = otf_to_c_action,
                                         suffix = '.c',
                                         src_suffix = '.otf')

def generate(env, **kw):
    env.Append(BUILDERS = {'OTF_TO_H': otf_to_h_builder})
    env.Append(BUILDERS = {'OTF_TO_C': otf_to_c_builder})

def exists(env):
    return True
