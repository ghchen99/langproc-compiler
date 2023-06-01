class x(object):
	__slots__ = ('y', 'z')

def f():
	g = x()
	g.y = 17
	g.z = 13
	return g.y + g.z

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
