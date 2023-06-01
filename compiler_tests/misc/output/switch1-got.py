def g(x):
	if ( x = 1 ) : 
		return 10
	if ( x = 2 || x = 1 ) : 
		return 11
	if ( x = 3 || x = 1 || x = 2 ) : 
		return 13
	else :
		return 12


# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
