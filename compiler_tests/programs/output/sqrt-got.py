def bsqrt(lo, hi, val):
	while lo + 1 < hi:
		mid=lo + hi >> 1
		sqr=mid * mid
		if (sqr <= val) :
			lo = mid
		else :
			hi = mid
	if (lo * lo < val) :
		return hi
	else :
		return lo

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
