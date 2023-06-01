class x(object):
	__slots__ = ('y')

def f():
	z = x()
	z.y = 13
	return z.y

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
