# Copyright 2023 Eric Smith
# SPDX-License-Identifier: GPL-3.0-only

conf_file = 'voyager-lcd.conf'
vars = Variables(conf_file, ARGUMENTS)
vars.AddVariables(EnumVariable ('target',
                                help = 'execution target platform',
                                allowed_values = ('posix', 'win64'),
                                default = 'posix',
                                ignorecase = True))

env = Environment(variables = vars)

vars.Save(conf_file, env)
Help(vars.GenerateHelpText(env))


platform = env['PLATFORM']
target = env['target']

build_dir = 'build/' + target

# include build dir in path, necessary for generated sources
env.Append(CPPPATH = '.')
env.Append(CPATH = '.')


if platform == 'posix' and target == 'posix':
    env.PrependENVPath('PATH', '/usr/lib64/qt6/libexec')

elif platform == 'posix' and target == 'win64':
    env['CC'] = 'x86_64-w64-mingw32-gcc'
    env['CXX'] = 'x86_64-w64-mingw32-g++'
    env['QT6DIR'] = '/usr/x86_64-w64-mingw32/sys-root/mingw'
    env['QT6BINDIR'] = '/usr/lib64/qt6'

else:
    print(f'Don\'t know how to build target {target} on platform {platform}')
    Exit(2)


SConscript('src/SConscript',
	   variant_dir = build_dir,
           duplicate = False,
           exports = 'env' )

