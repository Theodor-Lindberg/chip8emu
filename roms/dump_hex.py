from argparse import ArgumentParser

def format_hex(value: int) -> str:
	""" Format an integer to a readible hex representation. """
	return '0x{0:0{1}X}'.format(value, 4)

def disassemble_file(filepath: str) -> None:
	""" Go through a file byte by byte and dump its content as hex. """
	with open(filepath, 'rb') as f:
		address = 0x200
		while True:
			two_bytes = f.read(2)
			if not two_bytes:
				break;
			print(format_hex(address) + "\t:\t" + format_hex(int(two_bytes.hex(), 16)))
			address += 2


if __name__ == '__main__':
	parser = ArgumentParser()
	parser.add_argument('-f', '--file', dest='filepath', type=str,
            help='the relative path to the file')
	args = parser.parse_args()
	disassemble_file(args.filepath)
