compileTestsFlag = ARGUMENTS.get('test', '')
compileTests = (compileTestsFlag != '')

debugFlag = ARGUMENTS.get('debug', '')
debug = (debugFlag != '')

########################################################################################################

includeDirectories = ['.']
libraryDirectories = ['/usr/lib', '/usr/X11R6/lib']

commonLibs = ['GL', 'GLU', 'glut']
testLibs = commonLibs + []
mainLibs = commonLibs + ['QtOpenGL', 'QtGui', 'QtCore']

ccflags = '-std=c++0x'
if debug:
	ccflags += ' -g'
else:
	ccflags += ' -O3 -fopenmp'

linkflags = ''
if not debug:
	linkflags += ' -fopenmp'

########################################################################################################

env = Environment(CC = 'g++', CCFLAGS = ccflags, LINKFLAGS = linkflags, CPPPATH = includeDirectories)

env['BUILD_ROOT'] = Dir('.')
env['QT4DIR'] = '/usr'
env['ENV']['PKG_CONFIG_PATH'] = '/usr/lib/qt4/pkg-config'

env.Tool('qt4')
env.EnableQt4Modules(['QtGui', 'QtCore', 'QtOpenGL'])

########################################################################################################

tracerSourceFiles = Split("""
util/implementation/Util.cpp
tracer/implementation/Ray.cpp
geometry/implementation/Shape.cpp
geometry/implementation/Sphere.cpp
tracer/implementation/Scene.cpp
tracer/implementation/Pathtracer.cpp
""")

libtrace = env.Library('trace', source = tracerSourceFiles, LIBPATH = libraryDirectories)

sourceFiles = Split("""
				gui/implementation/GLWidget.cpp
				gui/implementation/MainWindow.cpp
				gui/implementation/main.cpp
				""")

mocHeaderFiles = Split("""
					gui/interface/GLWidget.hpp
					gui/interface/MainWindow.hpp
					""")

########################################################################################################

mocs = [env.Moc4(header) for header in mocHeaderFiles]

if compileTests:
	pass
else:
	env.Program(target = 'pathtracer', source = sourceFiles + mocs, LIBPATH = libraryDirectories, LIBS = libtrace + mainLibs)
