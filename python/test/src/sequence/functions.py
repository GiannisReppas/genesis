import sys
import unittest

sys.path.append('./genesis_bindings')

from mylibgenesis.genesis.utils import *
from mylibgenesis.genesis.sequence import *

class FastaTest(unittest.TestCase):

	def test_characteristics(self):
		infile = "./test/data/sequence/dna_10.fasta"
		sset = SequenceSet()
		FastaReader().read( from_file(infile), sset)

		# CHARACTERISTICS-1
		if not validate_chars( sset, nucleic_acid_codes_all() ):
			print("Error at CHARACTERISTICS-1")

		# CHARACTERISTICS-2
		if 4600 != total_length( sset ):
			print("Error at CHARACTERISTICS-2")
		# CHARACTERISTICS-3
		if not is_alignment( sset ):
			print("Error at CHARACTERISTICS-3")
		# CHARACTERISTICS-4
		if 0.1508695652173913 != gapyness( sset, nucleic_acid_codes_undetermined() ):
			print("Error at CHARACTERISTICS-4 ")

		sh = site_histogram( sset );
		bf = base_frequencies( sset, nucleic_acid_codes_plain() );

		# CHARACTERISTICS-5
		if 694 !=  sh['-']:
			print("Error at CHARACTERISTICS-5")
		# CHARACTERISTICS-6
		if 786 !=  sh['A']:
			print("Error at CHARACTERISTICS-6")
		# CHARACTERISTICS-7
		if 1175 != sh['C']:
			print("Error at CHARACTERISTICS-7")
		# CHARACTERISTICS-8
		if 1100 != sh['G']:
			print("Error at CHARACTERISTICS-8")
		# CHARACTERISTICS-9
		if 845 !=  sh['T']:
			print("Error at CHARACTERISTICS-9")

		# CHARACCTERISTICS-10
		if 0.20122887864823349 != bf['A']:
			print("Error at CHARACTERISTICS-10")
		# CHARACTERISTICS-11
		if 0.30081925243215568 != bf['C']:
			print("Error at CHARACTERISTICS-11")
		# CHARACTERISTICS-12
		if 0.2816180235535074 !=  bf['G']:
			print("Error at CHARACTERISTICS-12")
		# CHARACTERISTICS-13
		if 0.21633384536610342 != bf['T']:
			print("Error at CHARACTERISTICS-13")

if __name__ == '__main__':
    unittest.main()
