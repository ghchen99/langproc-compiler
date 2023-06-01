class x(object):
	__slots__ = ('y')

def f():
	y = x()
	return 13

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
