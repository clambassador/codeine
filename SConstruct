for i in range(0, 10):
    print ""
common = Split("""../ib/libib.a
	       """)
mains = dict()
mains['codeine.cc'] = 'codeine'

libs = Split("""ncurses
	     pthread
	     """)
env = Environment(CXX="ccache clang++ -I..", CPPFLAGS="-D_FILE_OFFSET_BITS=64 -Wall -g --std=c++11 -pthread", LIBS=libs, CPPPATH="..")
env['ENV']['TERM'] = 'xterm'

Decider('MD5')
for i in mains:
	env.Program(source = [i] + common, target = mains[i])
