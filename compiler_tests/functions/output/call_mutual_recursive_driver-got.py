def r1(n)

def r2(n):
	if (n == 0) :
		return 1
	else :
		return r1(n - 1) + r1(n - 1)
def main():
	return -(r1(5) == 32)

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
