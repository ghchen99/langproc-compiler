def f():
	i = 0
	x = [8]
	acc = 0
	i = 8
	while (i < 16):
		x[i - 8]=i
		i++

	acc = 0
	i = 0
	while (i < 8):
		acc = acc + x[i + 0]
		i++

	return acc

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
