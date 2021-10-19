def hexuid(binary: str) -> str:
    i = 0
    hexadecimal = []
    while (4*i + 3 < len(binary)):
        hexadecimal.append(hex(int(binary[4*i:4*i+4], 2)))
        i += 1
        
    return "".join([x[2:] for x in hexadecimal])
