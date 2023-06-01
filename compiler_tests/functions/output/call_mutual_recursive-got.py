def r2(n)

def r1(n):
	if (n == 0) :
		return 1
	else :
		return r2(n - 1) + r2(n - 1)

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
