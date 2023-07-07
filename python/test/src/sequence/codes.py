import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

class CodesTest(unittest.TestCase):

	def test_code_ambiguities(self):
		codes = nucleic_acid_codes_plain() + nucleic_acid_codes_degenerated() + "N-"

		# CODE_AMBIGUITIES-1
		for code in codes:
			code_string = nucleic_acid_ambiguities( code )
			code_char   = nucleic_acid_ambiguity_code( code_string )
			if code != code_char:
				print("Error at CODE_AMBIGUITIES-1")

	def test_code_containment(self):
		if not nucleic_acid_code_containment( 'A', 'A' ):
			print("Error at CODE_CONTAINMENT-1")
		if not nucleic_acid_code_containment( 'C', 'C' ):
			print("Error at CODE_CONTAINMENT-2")
		if not nucleic_acid_code_containment( 'G', 'G' ):
			print("Error at CODE_CONTAINMENT-3")
		if not nucleic_acid_code_containment( 'T', 'T' ):
			print("Error at CODE_CONTAINMENT-4")

		if not nucleic_acid_code_containment( 'A', 'W' ):
			print("Error at CODE_CONTAINMENT-5")
		if not nucleic_acid_code_containment( 'T', 'W' ):
			print("Error at CODE_CONTAINMENT-6")
		if not nucleic_acid_code_containment( 'C', 'H' ):
			print("Error at CODE_CONTAINMENT-7")

		if nucleic_acid_code_containment( 'C', 'D' ):
			print("Error at CODE_CONTAINMENT-8")
		if nucleic_acid_code_containment( 'A', 'T' ):
			print("Error at CODE_CONTAINMENT-9")
		if nucleic_acid_code_containment( 'A', 'Y' ):
			print("Error at CODE_CONTAINMENT-10")

		if not nucleic_acid_code_containment( '-', 'C', True ):
			print("Error at CODE_CONTAINMENT-11")
		if not nucleic_acid_code_containment( '-', 'H', True ):
			print("Error at CODE_CONTAINMENT-12")

		if nucleic_acid_code_containment( '-', 'C', False ):
			print("Error at CODE_CONTAINMENT-13")
		if nucleic_acid_code_containment( '-', 'H', False ):
			print("Error at CODE_CONTAINMENT-14")


if __name__ == '__main__':
    unittest.main()
