def f():
	x = [8]
	x[0]=23
	return x[0]

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
