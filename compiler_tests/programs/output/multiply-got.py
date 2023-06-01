def multiply(x, y):
	acc=0
	if (x < 0) :
		return -(multiply(-(x), y))
	while x > 0:
		acc += y
		x--
	return acc

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
