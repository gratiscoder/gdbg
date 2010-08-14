VariantDir('out', 'src', duplicate=0)
env = Environment()
env.ParseConfig("pkg-config --libs --cflags gtk+-2.0 vte")
env.Program(target='out/gdbg', source=['out/main.c'])

