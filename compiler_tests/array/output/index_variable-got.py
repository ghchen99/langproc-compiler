def f():
	i = 0
	x = [8]
	i = 0
	while (i < 8):
		x[i]=i
		i++

	return x[4]

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
