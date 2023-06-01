def f(n):
	if (n == 0) :
		return 0
	return n + f(n - 1)

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
