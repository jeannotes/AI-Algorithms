
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("echo", help="dffff",type=int)
args = parser.parse_args()
print(args.echo**2)